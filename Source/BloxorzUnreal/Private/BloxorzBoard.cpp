#include "BloxorzBoard.h"
#include "Camera/CameraComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
    constexpr float TileThickness = 20.f;
    FLinearColor TileColor(EBloxorzTileType Type)
    {
        switch (Type)
        {
        case EBloxorzTileType::Fragile: return FLinearColor(0.38f, 0.55f, 0.64f);
        case EBloxorzTileType::Switch:  return FLinearColor(0.05f, 0.75f, 0.92f);
        case EBloxorzTileType::Bridge:  return FLinearColor(0.82f, 0.48f, 0.12f);
        case EBloxorzTileType::Goal:    return FLinearColor(0.08f, 0.02f, 0.12f);
        default:                        return FLinearColor(0.11f, 0.16f, 0.23f);
        }
    }
}

ABloxorzBoard::ABloxorzBoard()
{
    PrimaryActorTick.bCanEverTick = true;
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = SceneRoot;

    NormalTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("NormalTiles")); NormalTiles->SetupAttachment(SceneRoot);
    FragileTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FragileTiles")); FragileTiles->SetupAttachment(SceneRoot);
    SwitchTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SwitchTiles")); SwitchTiles->SetupAttachment(SceneRoot);
    BridgeTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BridgeTiles")); BridgeTiles->SetupAttachment(SceneRoot);
    GoalTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GoalTiles")); GoalTiles->SetupAttachment(SceneRoot);
    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block")); BlockMesh->SetupAttachment(SceneRoot);
    BlockMesh->SetCastShadow(true);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); Camera->SetupAttachment(SceneRoot); Camera->bAutoActivate = true;
    TitleText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Title")); TitleText->SetupAttachment(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded())
    {
        for (UInstancedStaticMeshComponent* C : {NormalTiles.Get(), FragileTiles.Get(), SwitchTiles.Get(), BridgeTiles.Get(), GoalTiles.Get()}) C->SetStaticMesh(Cube.Object);
        BlockMesh->SetStaticMesh(Cube.Object);
    }
}

void ABloxorzBoard::BeginPlay()
{
    Super::BeginPlay();
    if (Level.Tiles.IsEmpty()) BuildShowcaseLevel();
    State.Block = Level.Start;
    LastValidState = State;
    BuildBoardVisuals();
    SnapBlock(State.Block);
}

void ABloxorzBoard::BuildShowcaseLevel()
{
    // Faithful port of Unity Level_14: both switch behaviors, linked bridges,
    // fragile support, gaps, and an upright-only goal in one compact level.
    Level.LevelId = TEXT("Unity_Level_14_Showcase");
    Level.GridSize = FIntPoint(7, 8);
    Level.Start = {FIntPoint(0,0), EBloxorzOrientation::Standing};
    Level.Goal = FIntPoint(0,5);
    auto Add = [this](int32 X, int32 Y, EBloxorzTileType Type, FName Id=NAME_None, TArray<FName> Targets={}, EBloxorzSwitchBehavior Behavior=EBloxorzSwitchBehavior::Toggle)
    {
        FBloxorzTile T; T.Position=FIntPoint(X,Y); T.Type=Type; T.Id=Id; T.Targets=MoveTemp(Targets); T.SwitchBehavior=Behavior; Level.Tiles.Add(MoveTemp(T));
    };
    Add(0,0,EBloxorzTileType::Normal); Add(0,1,EBloxorzTileType::Normal); Add(0,2,EBloxorzTileType::Normal);
    Add(0,3,EBloxorzTileType::Switch,TEXT("sw1"),{TEXT("sw1")});
    Add(1,0,EBloxorzTileType::Normal); Add(1,1,EBloxorzTileType::Normal); Add(1,2,EBloxorzTileType::Normal); Add(1,3,EBloxorzTileType::Normal);
    Add(2,3,EBloxorzTileType::Normal); Add(3,3,EBloxorzTileType::Bridge,TEXT("sw1"));
    Add(3,1,EBloxorzTileType::Switch,TEXT("sw2"),{TEXT("br1")},EBloxorzSwitchBehavior::HeavyOneShot);
    Add(4,1,EBloxorzTileType::Normal); Add(4,2,EBloxorzTileType::Normal); Add(4,3,EBloxorzTileType::Fragile); Add(4,4,EBloxorzTileType::Normal); Add(4,5,EBloxorzTileType::Normal);
    Add(5,1,EBloxorzTileType::Normal); Add(5,2,EBloxorzTileType::Normal); Add(5,3,EBloxorzTileType::Fragile); Add(5,4,EBloxorzTileType::Normal); Add(5,5,EBloxorzTileType::Normal);
    Add(3,5,EBloxorzTileType::Bridge,TEXT("br1")); Add(3,6,EBloxorzTileType::Normal); Add(3,7,EBloxorzTileType::Normal);
    Add(2,6,EBloxorzTileType::Fragile); Add(2,7,EBloxorzTileType::Fragile); Add(1,6,EBloxorzTileType::Fragile); Add(1,7,EBloxorzTileType::Fragile);
    Add(0,6,EBloxorzTileType::Normal); Add(0,7,EBloxorzTileType::Normal); Add(0,5,EBloxorzTileType::Goal);
}

void ABloxorzBoard::BuildBoardVisuals()
{
    UMaterialInterface* BaseMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    auto Configure = [BaseMat](UInstancedStaticMeshComponent* C, EBloxorzTileType Type)
    {
        C->ClearInstances();
        if (BaseMat) { UMaterialInstanceDynamic* M = UMaterialInstanceDynamic::Create(BaseMat, C); M->SetVectorParameterValue(TEXT("Color"), TileColor(Type)); C->SetMaterial(0,M); }
    };
    Configure(NormalTiles,EBloxorzTileType::Normal); Configure(FragileTiles,EBloxorzTileType::Fragile); Configure(SwitchTiles,EBloxorzTileType::Switch); Configure(BridgeTiles,EBloxorzTileType::Bridge); Configure(GoalTiles,EBloxorzTileType::Goal);
    for (const FBloxorzTile& T : Level.Tiles)
    {
        UInstancedStaticMeshComponent* C = NormalTiles;
        if(T.Type==EBloxorzTileType::Fragile) C=FragileTiles; else if(T.Type==EBloxorzTileType::Switch) C=SwitchTiles; else if(T.Type==EBloxorzTileType::Bridge) C=BridgeTiles; else if(T.Type==EBloxorzTileType::Goal) C=GoalTiles;
        const float HeightScale = T.Type==EBloxorzTileType::Switch ? .14f : .2f;
        C->AddInstance(FTransform(FRotator::ZeroRotator, FVector(T.Position.X*CellSize,T.Position.Y*CellSize,-TileThickness*.5f), FVector(CellSize/100.f*.92f,CellSize/100.f*.92f,HeightScale)));
    }
    if (BaseMat) { UMaterialInstanceDynamic* M = UMaterialInstanceDynamic::Create(BaseMat, BlockMesh); M->SetVectorParameterValue(TEXT("Color"),FLinearColor(0.86f,0.91f,0.98f)); BlockMesh->SetMaterial(0,M); }
    BlockMesh->SetRelativeScale3D(FVector(CellSize/100.f*.78f,CellSize/100.f*.78f,CellSize/100.f*1.78f));
    const FVector Center((Level.GridSize.X-1)*CellSize*.5f,(Level.GridSize.Y-1)*CellSize*.5f,0);
    Camera->SetRelativeLocation(Center+FVector(-780,-900,1050));
    Camera->SetRelativeRotation((Center-Camera->GetRelativeLocation()).Rotation());
    Camera->SetFieldOfView(42.f);
    TitleText->SetText(FText::FromString(TEXT("OBSIDIAN FOLD"))); TitleText->SetTextRenderColor(FColor(80,220,255)); TitleText->SetWorldSize(38.f);
    TitleText->SetHorizontalAlignment(EHTA_Center); TitleText->SetRelativeLocation(Center+FVector(0,360,180)); TitleText->SetRelativeRotation(FRotator(90,0,0));
    RefreshBridgeVisuals();
}

void ABloxorzBoard::RefreshBridgeVisuals()
{
    BridgeTiles->ClearInstances();
    for (const FBloxorzTile& T : Level.Tiles) if (T.Type==EBloxorzTileType::Bridge && State.Flags.FindRef(T.Id)!=0)
        BridgeTiles->AddInstance(FTransform(FRotator::ZeroRotator,FVector(T.Position.X*CellSize,T.Position.Y*CellSize,-TileThickness*.5f),FVector(CellSize/100.f*.92f,CellSize/100.f*.92f,.2f)));
}

FVector ABloxorzBoard::BlockCenter(const FBloxorzBlockState& B) const
{
    FVector P(B.Anchor.X*CellSize,B.Anchor.Y*CellSize,0);
    if(B.Orientation==EBloxorzOrientation::Standing) P.Z=CellSize*.89f;
    else { P.Z=CellSize*.39f; if(B.Orientation==EBloxorzOrientation::LyingX) P.X+=CellSize*.5f; else P.Y+=CellSize*.5f; }
    return P;
}
FQuat ABloxorzBoard::BlockRotation(const FBloxorzBlockState& B) const
{
    if(B.Orientation==EBloxorzOrientation::LyingX) return FQuat(FVector::YAxisVector,PI*.5f);
    if(B.Orientation==EBloxorzOrientation::LyingY) return FQuat(FVector::XAxisVector,-PI*.5f);
    return FQuat::Identity;
}
void ABloxorzBoard::SnapBlock(const FBloxorzBlockState& B){ BlockMesh->SetRelativeLocationAndRotation(BlockCenter(B),BlockRotation(B)); }

void ABloxorzBoard::RequestMove(EBloxorzDirection Direction)
{
    if(Phase!=EPhase::Idle || bWon) return;
    const FBloxorzMoveResult R=FBloxorzSimulation::ResolveMove(Level,State,Direction);
    AnimFrom=State.Block; AnimTo=R.AttemptedBlock; AnimDirection=Direction; PhaseTime=0; ++MoveCount;
    if(R.Outcome==EBloxorzMoveOutcome::Valid){ State=R.State; LastValidState=State; Phase=EPhase::Rolling; RefreshBridgeVisuals(); }
    else Phase=EPhase::Falling;
}

void ABloxorzBoard::Tick(float Dt)
{
    Super::Tick(Dt); if(Phase==EPhase::Idle) return; PhaseTime+=Dt;
    if(Phase==EPhase::Completing)
    {
        const float Pulse=1.f+FMath::Sin(PhaseTime*8.f)*.025f;
        BlockMesh->SetRelativeScale3D(FVector(CellSize/100.f*.78f,CellSize/100.f*.78f,CellSize/100.f*1.78f)*Pulse);
        if(PhaseTime>1.2f){ BlockMesh->SetRelativeScale3D(FVector(CellSize/100.f*.78f,CellSize/100.f*.78f,CellSize/100.f*1.78f)); Phase=EPhase::Idle; }
        return;
    }
    const float Duration=Phase==EPhase::Falling?FallDuration:RollDuration;
    const float A=FMath::Clamp(PhaseTime/Duration,0.f,1.f);
    const float Ease=FMath::InterpEaseInOut(0.f,1.f,A,2.2f);
    FVector P=FMath::Lerp(BlockCenter(AnimFrom),BlockCenter(AnimTo),Ease); P.Z+=FMath::Sin(Ease*PI)*CellSize*.12f;
    FQuat Q=FQuat::Slerp(BlockRotation(AnimFrom),BlockRotation(AnimTo),Ease);
    if(Phase==EPhase::Falling) P.Z-=CellSize*3.f*Ease*Ease;
    BlockMesh->SetRelativeLocationAndRotation(P,Q);
    if(A<1.f) return;
    if(Phase==EPhase::Falling){ FinishFall(); return; }
    SnapBlock(State.Block);
    if(FBloxorzSimulation::IsWin(Level,State)){ bWon=true; Phase=EPhase::Completing; PhaseTime=0; }
    else Phase=EPhase::Idle;
}

void ABloxorzBoard::FinishFall(){ State=LastValidState; SnapBlock(State.Block); Phase=EPhase::Idle; }
void ABloxorzBoard::Restart(){ State={}; State.Block=Level.Start; LastValidState=State; MoveCount=0; bWon=false; Phase=EPhase::Idle; RefreshBridgeVisuals(); SnapBlock(State.Block); }
FString ABloxorzBoard::GetStatusText() const { if(bWon) return TEXT("LEVEL COMPLETE  •  R TO REPLAY"); if(Phase==EPhase::Falling) return TEXT("NO SUPPORT — RECOVERING"); return TEXT("WASD / ARROWS TO ROLL  •  R TO RESTART"); }
