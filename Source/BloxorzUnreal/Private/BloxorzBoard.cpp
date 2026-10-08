#include "BloxorzBoard.h"
#include "BloxorzCampaign.h"
#include "Camera/CameraComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Engine/World.h"
#include "UnrealClient.h"

namespace
{
    const FLinearColor Stone(.105f,.16f,.19f), Cyan(.04f,.8f,.85f), Gold(.86f,.47f,.12f);
    UMaterialInstanceDynamic* Material(UObject* Owner, FLinearColor Color, float Metal, float Rough, float Glow=0)
    {
        auto* Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Art/M_Surface.M_Surface"));
        if(!Base) Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
        auto* M=UMaterialInstanceDynamic::Create(Base,Owner);
        M->SetVectorParameterValue(TEXT("Color"),Color);
        M->SetScalarParameterValue(TEXT("Metallic"),Metal);
        M->SetScalarParameterValue(TEXT("Roughness"),Rough);
        M->SetScalarParameterValue(TEXT("Glow"),Glow);
        return M;
    }
    void InstanceColor(UInstancedStaticMeshComponent* C,int32 I,FLinearColor Color)
    {
        C->SetCustomDataValue(I,0,Color.R,false); C->SetCustomDataValue(I,1,Color.G,false); C->SetCustomDataValue(I,2,Color.B,false);
    }
}

ABloxorzBoard::ABloxorzBoard()
{
    PrimaryActorTick.bCanEverTick=true;
    SceneRoot=CreateDefaultSubobject<USceneComponent>(TEXT("Root")); RootComponent=SceneRoot;
    Bodies=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileBases"));
    Caps=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileSurfaces"));
    Marks=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileSymbols"));
    Sparks=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FeedbackParticles"));
    for(auto* C:{Bodies.Get(),Caps.Get(),Marks.Get(),Sparks.Get()}){C->SetupAttachment(SceneRoot); C->SetCollisionEnabled(ECollisionEnabled::NoCollision); C->NumCustomDataFloats=3;}
    Sparks->SetCastShadow(false); Marks->SetCastShadow(false); Caps->SetCastShadow(false);
    BlockMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RollingBlock")); BlockMesh->SetupAttachment(SceneRoot);
    BlockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Ground=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backdrop")); Ground->SetupAttachment(SceneRoot);
    Ground->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("PuzzleCamera")); Camera->SetupAttachment(SceneRoot);
    Camera->SetFieldOfView(38); Camera->bConstrainAspectRatio=false;
    Camera->PostProcessSettings.bOverride_AutoExposureMethod=true;
    Camera->PostProcessSettings.AutoExposureMethod=EAutoExposureMethod::AEM_Manual;
    Camera->PostProcessSettings.bOverride_AutoExposureBias=true;
    Camera->PostProcessSettings.AutoExposureBias=0;
    Camera->PostProcessSettings.bOverride_AutoExposureApplyPhysicalCameraExposure=true;
    Camera->PostProcessSettings.AutoExposureApplyPhysicalCameraExposure=false;
    Camera->PostProcessSettings.bOverride_BloomIntensity=true; Camera->PostProcessSettings.BloomIntensity=.25f;
    Camera->PostProcessSettings.bOverride_VignetteIntensity=true; Camera->PostProcessSettings.VignetteIntensity=.32f;
    Camera->PostProcessSettings.bOverride_MotionBlurAmount=true; Camera->PostProcessSettings.MotionBlurAmount=0;
}

void ABloxorzBoard::BeginPlay()
{
    Super::BeginPlay();
    Campaign=MakeBloxorzCampaign();
    if(!Level.Tiles.IsEmpty()) Campaign={Level};
    if(UGameplayStatics::DoesSaveGameExist(TEXT("ObsidianFoldProgress"),0))Progress=Cast<UBloxorzProgress>(UGameplayStatics::LoadGameFromSlot(TEXT("ObsidianFoldProgress"),0));
    if(!Progress) Progress=Cast<UBloxorzProgress>(UGameplayStatics::CreateSaveGameObject(UBloxorzProgress::StaticClass()));
    for(const TCHAR* Name:{TEXT("Roll"),TEXT("Land"),TEXT("Switch"),TEXT("Fall"),TEXT("Complete")})
        Sounds.Add(LoadObject<USoundWave>(nullptr,*FString::Printf(TEXT("/Game/Audio/%s.%s"),Name,Name)));
    if(!LandingEffect)LandingEffect=LoadObject<UNiagaraSystem>(nullptr,TEXT("/Game/FX/NS_Landing.NS_Landing"));
    if(!CompletionEffect)CompletionEffect=LoadObject<UNiagaraSystem>(nullptr,TEXT("/Game/FX/NS_Complete.NS_Complete"));
    int32 Start=0; FParse::Value(FCommandLine::Get(),TEXT("BloxorzLevel="),Start);
    bSmoke=FParse::Param(FCommandLine::Get(),TEXT("BloxorzCapture"));
    bReplay=FParse::Value(FCommandLine::Get(),TEXT("BloxorzReplay="),ReplayPath);
    bProfile=FParse::Param(FCommandLine::Get(),TEXT("BloxorzProfile"));
    LoadLevel(Start);
    if(auto* PC=GetWorld()->GetFirstPlayerController()) { PC->SetViewTarget(this); PC->bAutoManageActiveCameraTarget=false; }
}

void ABloxorzBoard::LoadLevel(int32 Index)
{
    if(Campaign.IsEmpty()) return;
    LevelIndex=FMath::Clamp(Index,0,Campaign.Num()-1); Level=Campaign[LevelIndex];
    State={}; State.Block=Level.Start; MoveCount=0; Revives=3; bWon=false; bBuffered=false; Phase=EPhase::Idle; PhaseTime=0; bMenu=false;
    Particles.Reset(); Sparks->ClearInstances();
    BuildVisuals(); SnapBlock(); LandingAge=10;
}

void ABloxorzBoard::BuildVisuals()
{
    auto* Cube=LoadObject<UStaticMesh>(nullptr,TEXT("/Game/Art/SM_RoundedCube.SM_RoundedCube"));
    if(!Cube) Cube=LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube.Cube"));
    for(auto* C:{Bodies.Get(),Caps.Get(),Marks.Get(),Sparks.Get()}) { C->ClearInstances(); C->SetStaticMesh(Cube); }
    BlockMesh->SetStaticMesh(Cube); Ground->SetStaticMesh(Cube);
    Bodies->SetMaterial(0,Material(this,FLinearColor(.055f,.075f,.085f),.6f,.32f));
    auto* Instanced=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Art/M_Instanced.M_Instanced"));
    Caps->SetMaterial(0,Instanced?Instanced:Material(this,Stone,.3f,.35f));
    Marks->SetMaterial(0,Material(this,Cyan,.5f,.24f,1.6f));
    Sparks->SetMaterial(0,Material(this,Gold,.25f,.25f,3.f)); Sparks->SetCastShadow(false);
    BlockMesh->SetMaterial(0,Material(this,FLinearColor(.92f,.61f,.25f),.72f,.22f));
    BlockMesh->SetRelativeScale3D(FVector(.98f,.98f,1.98f)*CellSize/100.f);
    Ground->SetMaterial(0,Material(this,FLinearColor(.018f,.035f,.047f),.12f,.68f));
    BoundsMin=FVector(FLT_MAX); BoundsMax=FVector(-FLT_MAX); TileVisuals.Reset();
    auto Mark=[&](FVector P,FVector Scale,float Yaw=0){ Marks->AddInstance(FTransform(FRotator(0,Yaw,0),P,Scale*CellSize/100.f)); };
    for(int32 I=0;I<Level.Tiles.Num();++I)
    {
        const auto& T=Level.Tiles[I]; if(T.Type==EBloxorzTileType::Empty) continue;
        FVector P(T.Position.X*CellSize,-T.Position.Y*CellSize,0);
        BoundsMin=BoundsMin.ComponentMin(P-FVector(CellSize*.5f,CellSize*.5f,0));
        BoundsMax=BoundsMax.ComponentMax(P+FVector(CellSize*.5f,CellSize*.5f,CellSize*2));
        if(T.Type==EBloxorzTileType::Goal)
        {
            // A real visual aperture: four frame segments, with no cap across the hole.
            for(int J=0;J<4;++J)
            {
                FVector Offset=J<2?FVector((J?1:-1)*CellSize*.48f,0,-8):FVector(0,(J==3?1:-1)*CellSize*.48f,-8);
                FVector Scale=J<2?FVector(.055f,1.f,.20f):FVector(.90f,.055f,.20f);
                Bodies->AddInstance(FTransform(FQuat::Identity,P+Offset,Scale*CellSize/100.f));
                Mark(P+Offset+FVector(0,0,13),J<2?FVector(.035f,.98f,.025f):FVector(.91f,.035f,.025f));
            }
            continue;
        }
        FTileVisual V; V.Tile=I; V.Open=T.Type==EBloxorzTileType::Bridge?0:1;
        V.Body=Bodies->AddInstance(FTransform(FQuat::Identity,P-FVector(0,0,21),FVector(.99f,.99f,.34f)*CellSize/100.f));
        V.Cap=Caps->AddInstance(FTransform(FQuat::Identity,P-FVector(0,0,4),FVector(.94f,.94f,.065f)*CellSize/100.f));
        const FLinearColor Color=T.Type==EBloxorzTileType::Fragile?FLinearColor(.34f,.22f,.14f):T.Type==EBloxorzTileType::Bridge?Gold:Stone;
        InstanceColor(Caps,V.Cap,Color); TileVisuals.Add(V);
        if(T.Type==EBloxorzTileType::Switch)
        {
            const bool Heavy=T.SwitchBehavior==EBloxorzSwitchBehavior::HeavyOneShot;
            if(Heavy){Mark(P+FVector(0,0,2),FVector(.38f,.045f,.025f),45);Mark(P+FVector(0,0,2),FVector(.38f,.045f,.025f),-45);}
            else for(int J=0;J<12;++J){float A=J*PI/6;Mark(P+FVector(FMath::Cos(A)*CellSize*.18f,FMath::Sin(A)*CellSize*.18f,2),FVector(.105f,.035f,.025f),FMath::RadiansToDegrees(A)+90);}
        }
        if(T.Type==EBloxorzTileType::Fragile)
        {
            Mark(P+FVector(-CellSize*.12f,0,1),FVector(.30f,.016f,.015f),-35);
            Mark(P+FVector(CellSize*.11f,CellSize*.04f,1),FVector(.23f,.016f,.015f),35);
        }
    }
    Caps->MarkRenderStateDirty();
    BoardCenter=(BoundsMin+BoundsMax)*.5f; BoardCenter.Z=CellSize*.35f;
    Ground->SetRelativeLocation(FVector(BoardCenter.X,BoardCenter.Y,-CellSize*1.9f));
    Ground->SetRelativeScale3D(FVector(300,300,.5f));
    UpdateTiles(0,true); LastAspect=0; FitCamera();
}

void ABloxorzBoard::FitCamera()
{
    int32 W=1600,H=900; if(auto* PC=GetWorld()->GetFirstPlayerController()) PC->GetViewportSize(W,H);
    const float Aspect=H>0?float(W)/H:16.f/9.f;
    if(FMath::IsNearlyEqual(Aspect,LastAspect,.002f)) return; LastAspect=Aspect;
    // +grid X reads screen-right; +grid Y reads screen-up. Mild yaw shows the block's sides.
    const FRotator R(-56,-82,0); Camera->SetRelativeRotation(R);
    const FVector Forward=R.Vector(), Right=FRotationMatrix(R).GetScaledAxis(EAxis::Y), Up=FRotationMatrix(R).GetScaledAxis(EAxis::Z);
    const float TanH=FMath::Tan(FMath::DegreesToRadians(Camera->FieldOfView*.5f));
    float Distance=700;
    for(int I=0;I<8;++I)
    {
        const FVector P((I&1)?BoundsMax.X:BoundsMin.X,(I&2)?BoundsMax.Y:BoundsMin.Y,(I&4)?BoundsMax.Z:BoundsMin.Z);
        const FVector D=P-BoardCenter;
        Distance=FMath::Max(Distance,FMath::Max(FMath::Abs(D.Dot(Right))/(TanH*.78f),FMath::Abs(D.Dot(Up))/(TanH/Aspect*.68f))-D.Dot(Forward));
    }
    CameraHome=BoardCenter-Forward*Distance; Camera->SetRelativeLocation(CameraHome);
}

FVector ABloxorzBoard::LogicalCenter(const FBloxorzBlockState& B,float C)
{
    return FVector((B.Anchor.X+(B.Orientation==EBloxorzOrientation::LyingX?.5f:0))*C,
                   -(B.Anchor.Y+(B.Orientation==EBloxorzOrientation::LyingY?.5f:0))*C,
                   B.Orientation==EBloxorzOrientation::Standing?C:C*.5f);
}
FVector ABloxorzBoard::RollDirection(EBloxorzDirection D)
{
    switch(D){case EBloxorzDirection::Up:return FVector(0,-1,0);case EBloxorzDirection::Down:return FVector(0,1,0);case EBloxorzDirection::Left:return FVector(-1,0,0);default:return FVector(1,0,0);}
}
FVector ABloxorzBoard::RollPivot(const FBloxorzBlockState& B,EBloxorzDirection D,float C)
{
    const FVector Dir=RollDirection(D);
    const bool LongAxis=(Dir.X!=0&&B.Orientation==EBloxorzOrientation::LyingX)||(Dir.Y!=0&&B.Orientation==EBloxorzOrientation::LyingY);
    FVector P=LogicalCenter(B,C)+Dir*C*(LongAxis?1.f:.5f); P.Z=0; return P;
}
void ABloxorzBoard::SnapBlock()
{
    FQuat Q=FQuat::Identity;
    if(State.Block.Orientation==EBloxorzOrientation::LyingX)Q=FQuat(FVector::YAxisVector,PI*.5f);
    if(State.Block.Orientation==EBloxorzOrientation::LyingY)Q=FQuat(FVector::XAxisVector,PI*.5f);
    BlockMesh->SetVisibility(true); BlockMesh->SetRelativeLocationAndRotation(LogicalCenter(State.Block,CellSize),Q);
}
void ABloxorzBoard::RequestMove(EBloxorzDirection D)
{
    if(bMenu||bWon) return;
    if(Phase==EPhase::Rolling){BufferedDirection=D;bBuffered=true;BufferAge=0;return;}
    if(Phase!=EPhase::Idle)return;
    Pending=FBloxorzSimulation::ResolveMove(Level,State,D); AnimFrom=State.Block;
    StartRotation=BlockMesh->GetRelativeRotation().Quaternion(); Pivot=RollPivot(AnimFrom,D,CellSize);
    Axis=FVector::CrossProduct(FVector::UpVector,RollDirection(D)); ++MoveCount; PhaseTime=0;Phase=EPhase::Rolling;
    PlayFeedback(0,.3f);
}
void ABloxorzBoard::FinishRoll()
{
    if(Pending.Outcome==EBloxorzMoveOutcome::Fell){Phase=EPhase::Falling;PhaseTime=0;bBuffered=false;PlayFeedback(3,.5f);return;}
    State=Pending.State; LandingAge=0;
    const FVector P=LogicalCenter(State.Block,CellSize);
    Burst(FVector(P.X,P.Y,5),6,65);PlayFeedback(1,.5f);
    // Ordinary landings use bounded mesh sparks. Reserve Niagara for meaningful interactions.
    if(LandingEffect&&!Pending.ChangedFlags.IsEmpty())UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),LandingEffect,GetActorTransform().TransformPosition(FVector(P.X,P.Y,3)),FRotator::ZeroRotator,FVector(.08f),true,true,ENCPoolMethod::AutoRelease);
    if(!Pending.ChangedFlags.IsEmpty()){PlayFeedback(2,.5f);Burst(FVector(P.X,P.Y,10),12,100);}
    if(FBloxorzSimulation::IsWin(Level,State))
    {
        bWon=true;bBuffered=false;Phase=EPhase::Completing;PhaseTime=0;SaveProgress();PlayFeedback(4,.6f);Burst(FVector(P.X,P.Y,10),28,180);
        if(CompletionEffect)UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),CompletionEffect,GetActorTransform().TransformPosition(P),FRotator::ZeroRotator,FVector(.35f));
    }
    else Phase=EPhase::Idle;
}
void ABloxorzBoard::UpdateTiles(float Dt,bool Snap)
{
    bool bChanged=false;
    for(auto& V:TileVisuals)
    {
        const auto& T=Level.Tiles[V.Tile]; const bool Bridge=T.Type==EBloxorzTileType::Bridge;
        const float Target=Bridge?(State.Flags.FindRef(T.Id)!=0?1.f:0.f):1.f;
        if(!Snap && V.Open==Target)continue;
        bChanged=true;
        V.Open=Snap?Target:FMath::FInterpConstantTo(V.Open,Target,Dt,4.5f);
        const FVector P(T.Position.X*CellSize,-T.Position.Y*CellSize,-(1-V.Open)*CellSize*1.6f);
        const float S=FMath::Max(.001f,V.Open);
        Bodies->UpdateInstanceTransform(V.Body,FTransform(FQuat::Identity,P-FVector(0,0,21),FVector(.99f,.99f,.34f)*CellSize/100.f*S),false,false);
        Caps->UpdateInstanceTransform(V.Cap,FTransform(FQuat::Identity,P-FVector(0,0,4),FVector(.94f,.94f,.065f)*CellSize/100.f*S),false,false);
    }
    if(bChanged){Bodies->MarkRenderStateDirty();Caps->MarkRenderStateDirty();}
}
void ABloxorzBoard::Burst(FVector P,int32 Count,float Speed)
{
    for(int I=0;I<Count&&Particles.Num()<100;++I)
    {
        const float A=I*2.399963f;FParticle F;F.Start=P;F.Velocity=FVector(FMath::Cos(A)*Speed,FMath::Sin(A)*Speed,Speed*(.5f+(I%3)*.2f));F.Life=.45f+(I%4)*.08f;F.Size=2.f+(I%3);Particles.Add(F);
    }
}
void ABloxorzBoard::PlayFeedback(int32 Index,float Volume)
{
    if(!bMuted&&Sounds.IsValidIndex(Index)&&Sounds[Index])UGameplayStatics::PlaySound2D(this,Sounds[Index],Volume);
}
void ABloxorzBoard::Tick(float Dt)
{
    Super::Tick(Dt);Elapsed+=Dt;FitCamera();
    // Bounded real-time smoke profiling. Do not combine with -benchmark's fixed timestep.
    if(bProfile && Elapsed>3) ProfileFrameTimes.Add(Dt*1000.f);
    if(bProfile && Elapsed>20)
    {
        ProfileFrameTimes.Sort();
        double Total=0;for(float Frame:ProfileFrameTimes)Total+=Frame;
        UE_LOG(LogTemp,Display,TEXT("BLOXORZ_PROFILE samples=%d mean_ms=%.3f p95_ms=%.3f"),ProfileFrameTimes.Num(),Total/FMath::Max(1,ProfileFrameTimes.Num()),ProfileFrameTimes[FMath::Clamp(FMath::FloorToInt(ProfileFrameTimes.Num()*.95f),0,ProfileFrameTimes.Num()-1)]);
        bProfile=false;FPlatformMisc::RequestExit(false);
    }
    if(bMenu)return;
    if(bReplay&&Elapsed>2)
    {
        ReplayFrameTotal+=Dt;++ReplayFrames;
        if(Phase==EPhase::Idle&&ReplayIndex<ReplayPath.Len())
        {
            const TCHAR C=ReplayPath[ReplayIndex++];
            RequestMove(C=='U'?EBloxorzDirection::Up:C=='D'?EBloxorzDirection::Down:C=='L'?EBloxorzDirection::Left:EBloxorzDirection::Right);
        }
        if(Phase==EPhase::Complete)
        {
            UE_LOG(LogTemp,Display,TEXT("BLOXORZ_REPLAY_SUCCESS level=%d moves=%d frames=%d avg_frame_ms=%.3f"),LevelIndex+1,MoveCount,ReplayFrames,ReplayFrameTotal*1000/FMath::Max(1,ReplayFrames));
            FScreenshotRequest::RequestScreenshot(FString::Printf(TEXT("Bloxorz_Complete_%02d.png"),LevelIndex+1),true,false);
            bReplay=false;
        }
        else if(Phase==EPhase::Failed){UE_LOG(LogTemp,Error,TEXT("BLOXORZ_REPLAY_FAILED at move=%d"),ReplayIndex);bReplay=false;}
    }
    LandingAge+=Dt; BufferAge+=Dt;
    Camera->SetRelativeLocation(CameraHome+FVector(0,0,CameraShakeStrength*FMath::Exp(-LandingAge*18)*FMath::Sin(LandingAge*55)));
    UpdateTiles(Dt); Sparks->ClearInstances();
    for(int I=Particles.Num()-1;I>=0;--I)
    {
        auto& P=Particles[I];P.Age+=Dt;if(P.Age>=P.Life){Particles.RemoveAtSwap(I);continue;}
        const FVector Loc=P.Start+P.Velocity*P.Age-FVector(0,0,160*P.Age*P.Age);
        Sparks->AddInstance(FTransform(FRotator(P.Age*180,P.Age*100,0),Loc,FVector(P.Size/100.f*(1-P.Age/P.Life))));
    }
    if(Phase==EPhase::Idle&&bBuffered){bBuffered=false;if(BufferAge<.35f)RequestMove(BufferedDirection);}
    PhaseTime+=Dt;
    if(Phase==EPhase::Rolling)
    {
        const float T=FMath::Clamp(PhaseTime/FMath::Max(.08f,RollDuration),0.f,1.f);
        const float A=T*T*(3-2*T);const FQuat Delta(Axis,A*PI*.5f);
        BlockMesh->SetRelativeLocationAndRotation(Pivot+Delta.RotateVector(LogicalCenter(AnimFrom,CellSize)-Pivot),Delta*StartRotation);
        if(T>=1)FinishRoll();
    }
    else if(Phase==EPhase::Falling)
    {
        const FVector End=LogicalCenter(Pending.AttemptedBlock,CellSize);
        const FQuat Q=FQuat(Axis,PI*.5f+PhaseTime*1.7f)*StartRotation;
        BlockMesh->SetRelativeLocationAndRotation(End+FVector(0,0,-CellSize*7*PhaseTime*PhaseTime),Q);
        if(PhaseTime>=FallDuration){Phase=EPhase::Failed;BlockMesh->SetVisibility(false);}
    }
    else if(Phase==EPhase::Completing)
    {
        BlockMesh->SetRelativeLocation(LogicalCenter(State.Block,CellSize)-FVector(0,0,CellSize*2.8f*FMath::Clamp(PhaseTime/.8f,0.f,1.f)));
        if(PhaseTime>1){Phase=EPhase::Complete;BlockMesh->SetVisibility(false);}
    }
    if(bSmoke&&Elapsed>4&&Elapsed-Dt<=4)FScreenshotRequest::RequestScreenshot(FString::Printf(TEXT("Bloxorz_Level_%02d.png"),LevelIndex+1),true,false);
}
void ABloxorzBoard::Restart(){LoadLevel(LevelIndex);}
void ABloxorzBoard::Revive(){if(Phase!=EPhase::Failed||Revives<=0)return;--Revives;Phase=EPhase::Idle;SnapBlock();Burst(LogicalCenter(State.Block,CellSize),10,80);}
void ABloxorzBoard::NextLevel(){LoadLevel((LevelIndex+1)%Campaign.Num());}
void ABloxorzBoard::PreviousLevel(){LoadLevel((LevelIndex+Campaign.Num()-1)%Campaign.Num());}
void ABloxorzBoard::ToggleMenu(){bMenu=!bMenu;bBuffered=false;}
void ABloxorzBoard::ToggleMute(){bMuted=!bMuted;}
void ABloxorzBoard::SaveProgress()
{
    if(bReplay||bSmoke||bProfile)return;
    if(!Progress)return;
    const int32 Old=Progress->BestMoves.FindRef(LevelIndex);
    if(Old==0||MoveCount<Old)Progress->BestMoves.Add(LevelIndex,MoveCount);
    Progress->Unlocked=FMath::Max(Progress->Unlocked,FMath::Min(LevelIndex+1,Campaign.Num()-1));
    UGameplayStatics::SaveGameToSlot(Progress,TEXT("ObsidianFoldProgress"),0);
}
FString ABloxorzBoard::GetStatusText() const
{
    if(bMenu)return TEXT("Take your time. Every move matters.");
    if(bWon)return LevelIndex==Campaign.Num()-1?TEXT("CAMPAIGN COMPLETE"):TEXT("LEVEL COMPLETE");
    if(Phase==EPhase::Failed)return TEXT("Find another way.");
    if(LevelIndex==0)return TEXT("Roll onto the cyan socket. Finish standing upright.");
    if(LevelIndex<5)return TEXT("Both cells need support. Plan where you stand.");
    if(LevelIndex<10)return TEXT("Cracked tiles support you only while lying flat.");
    return TEXT("Circle: toggle bridge. Cross: press upright, once.");
}
