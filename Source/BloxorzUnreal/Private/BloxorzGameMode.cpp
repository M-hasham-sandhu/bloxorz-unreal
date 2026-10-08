#include "BloxorzGameMode.h"
#include "BloxorzBoard.h"
#include "Components/LightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/Canvas.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

static ABloxorzBoard* Board(UWorld* W){for(TActorIterator<ABloxorzBoard> It(W);It;++It)return *It;return nullptr;}
ABloxorzGameMode::ABloxorzGameMode(){PlayerControllerClass=ABloxorzPlayerController::StaticClass();HUDClass=ABloxorzHUD::StaticClass();DefaultPawnClass=nullptr;}
void ABloxorzGameMode::BeginPlay()
{
    Super::BeginPlay();
    auto* B=Board(GetWorld());if(!B)B=GetWorld()->SpawnActor<ABloxorzBoard>();
    if(auto* PC=GetWorld()->GetFirstPlayerController()){PC->bAutoManageActiveCameraTarget=false;PC->SetViewTarget(B);}
    int32 LightPriority=1;
    auto Light=[this,&LightPriority](FRotator Rotation,float Intensity,FLinearColor Color)
    {
        auto* L=GetWorld()->SpawnActor<ADirectionalLight>(FVector::ZeroVector,Rotation);
        L->GetLightComponent()->SetMobility(EComponentMobility::Movable);
        L->GetLightComponent()->SetIntensity(Intensity);L->GetLightComponent()->SetLightColor(Color);
        L->GetLightComponent()->SetCastShadows(LightPriority==1); // Only the key light needs shadows.
        Cast<UDirectionalLightComponent>(L->GetLightComponent())->SetForwardShadingPriority(LightPriority--);
    };
    Light(FRotator(-55,-35,0),5.f,FLinearColor(1.f,.88f,.73f));
    Light(FRotator(-30,150,0),2.f,FLinearColor(.40f,.72f,1.f));
}
void ABloxorzPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();bShowMouseCursor=true;bAutoManageActiveCameraTarget=false;
    InputComponent->BindKey(EKeys::W,IE_Pressed,this,&ABloxorzPlayerController::MoveUp);InputComponent->BindKey(EKeys::Up,IE_Pressed,this,&ABloxorzPlayerController::MoveUp);
    InputComponent->BindKey(EKeys::S,IE_Pressed,this,&ABloxorzPlayerController::MoveDown);InputComponent->BindKey(EKeys::Down,IE_Pressed,this,&ABloxorzPlayerController::MoveDown);
    InputComponent->BindKey(EKeys::A,IE_Pressed,this,&ABloxorzPlayerController::MoveLeft);InputComponent->BindKey(EKeys::Left,IE_Pressed,this,&ABloxorzPlayerController::MoveLeft);
    InputComponent->BindKey(EKeys::D,IE_Pressed,this,&ABloxorzPlayerController::MoveRight);InputComponent->BindKey(EKeys::Right,IE_Pressed,this,&ABloxorzPlayerController::MoveRight);
    InputComponent->BindKey(EKeys::R,IE_Pressed,this,&ABloxorzPlayerController::RestartLevel);
    InputComponent->BindKey(EKeys::Enter,IE_Pressed,this,&ABloxorzPlayerController::Confirm);
    InputComponent->BindKey(EKeys::SpaceBar,IE_Pressed,this,&ABloxorzPlayerController::Confirm);
    InputComponent->BindKey(EKeys::Escape,IE_Pressed,this,&ABloxorzPlayerController::Menu);
    InputComponent->BindKey(EKeys::M,IE_Pressed,this,&ABloxorzPlayerController::Mute);
    InputComponent->BindKey(EKeys::PageDown,IE_Pressed,this,&ABloxorzPlayerController::Next);
    InputComponent->BindKey(EKeys::PageUp,IE_Pressed,this,&ABloxorzPlayerController::Previous);
    InputComponent->BindKey(EKeys::LeftMouseButton,IE_Pressed,this,&ABloxorzPlayerController::Click);
}
void ABloxorzPlayerController::MoveUp(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Up);}
void ABloxorzPlayerController::MoveDown(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Down);}
void ABloxorzPlayerController::MoveLeft(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Left);}
void ABloxorzPlayerController::MoveRight(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Right);}
void ABloxorzPlayerController::RestartLevel(){if(auto* B=Board(GetWorld()))B->Restart();}
void ABloxorzPlayerController::Confirm(){if(auto* B=Board(GetWorld())){if(B->IsMenuOpen())B->ToggleMenu();else if(B->HasWon())B->NextLevel();else if(B->IsDead())B->Revive();}}
void ABloxorzPlayerController::Menu(){if(auto* B=Board(GetWorld()))B->ToggleMenu();}
void ABloxorzPlayerController::Mute(){if(auto* B=Board(GetWorld()))B->ToggleMute();}
void ABloxorzPlayerController::Next(){if(auto* B=Board(GetWorld()))B->NextLevel();}
void ABloxorzPlayerController::Previous(){if(auto* B=Board(GetWorld()))B->PreviousLevel();}
void ABloxorzPlayerController::Click(){if(auto* H=Cast<ABloxorzHUD>(GetHUD()))H->HandleClick();}

void ABloxorzHUD::DrawHUD()
{
    Super::DrawHUD();auto* B=Board(GetWorld());if(!B||!Canvas)return;
    Buttons.Reset();
    const float Scale=FMath::Min(Canvas->SizeX/1440.f,Canvas->SizeY/900.f);
    const float W=Canvas->SizeX/Scale,H=Canvas->SizeY/Scale;
    const FLinearColor Ink(.87f,.92f,.91f),Muted(.43f,.57f,.60f),Accent(.20f,.85f,.81f),Panel(.017f,.032f,.043f,.96f);
    auto Text=[&](FString S,float X,float Y,float Size,FLinearColor C){DrawText(S,C,X*Scale,Y*Scale,GEngine->GetMediumFont(),Size*Scale,false);};
    auto Rect=[&](FLinearColor C,float X,float Y,float A,float D){DrawRect(C,X*Scale,Y*Scale,A*Scale,D*Scale);};
    auto Button=[&](FString Label,float X,float Y,float Width,FName Action)
    {
        float MX=0,MY=0;GetOwningPlayerController()->GetMousePosition(MX,MY);
        const FBox2D Box(FVector2D(X*Scale,Y*Scale),FVector2D((X+Width)*Scale,(Y+44)*Scale));
        const bool Hover=Box.IsInside(FVector2D(MX,MY));
        Rect(Hover?FLinearColor(.09f,.25f,.27f):FLinearColor(.04f,.09f,.11f),X,Y,Width,44);
        Rect(Hover?Accent:Muted,X,Y,2,44);Text(Label,X+16,Y+12,.9f,Ink);
        Buttons.Add({Box,Action});
    };
    Text(TEXT("O B S I D I A N   F O L D"),42,32,1.25f,Ink);
    Text(TEXT("A STUDY IN BALANCE"),43,63,.64f,Muted);
    Rect(Accent,42,94,52,2);
    Text(FString::Printf(TEXT("%02d / %02d"),B->GetLevelIndex()+1,B->GetLevelCount()),W-200,32,1.25f,Ink);
    Text(FString::Printf(TEXT("MOVES  %02d    BEST  %s"),B->GetMoveCount(),B->GetBest()?*FString::FromInt(B->GetBest()):TEXT("--")),W-270,65,.78f,Muted);
    Text(B->GetStatusText(),42,H-110,.95f,Ink);
    Text(TEXT("WASD / ARROWS   roll       R   restart       ESC   menu"),42,H-76,.76f,Muted);
    Text(TEXT("PGUP / PGDN   levels"),42,H-48,.65f,Muted);
    Button(B->IsMuted()?TEXT("SOUND OFF"):TEXT("SOUND ON"),W-184,H-82,142,TEXT("Mute"));
    if(B->IsMenuOpen()||B->IsDead()||B->HasWon())
    {
        Buttons.Reset(); // Modal panels must not activate obscured background controls.
        Rect(FLinearColor(.005f,.012f,.02f,.67f),0,0,W,H);
        const float X=(W-500)/2,Y=(H-300)/2;
        Rect(Panel,X,Y,500,300);Rect(Accent,X,Y,500,3);
        const FString Title=B->IsMenuOpen()?TEXT("PAUSED"):B->HasWon()?B->GetStatusText():TEXT("ONE STEP TOO FAR");
        Text(Title,X+32,Y+30,1.5f,Ink);
        Text(B->HasWon()?FString::Printf(TEXT("%d moves. A little more perspective."),B->GetMoveCount()):
             B->IsDead()?FString::Printf(TEXT("%d revives remaining. Or begin again."),B->GetRevives()):TEXT("A moment to see the whole board."),X+32,Y+83,.85f,Muted);
        if(B->IsMenuOpen())Button(TEXT("RESUME   /   ENTER"),X+32,Y+133,436,TEXT("Resume"));
        else if(B->HasWon())Button(TEXT("CONTINUE   /   ENTER"),X+32,Y+133,436,TEXT("Next"));
        else if(B->GetRevives()>0)Button(TEXT("REVIVE   /   ENTER"),X+32,Y+133,436,TEXT("Revive"));
        Button(TEXT("RESTART   /   R"),X+32,Y+190,210,TEXT("Restart"));
        Button(TEXT("NEXT LEVEL"),X+258,Y+190,210,TEXT("Next"));
        Text(TEXT("15 REFERENCE LEVELS  /  PROGRESS SAVED LOCALLY"),X+32,Y+260,.63f,Muted);
    }
}
void ABloxorzHUD::HandleClick()
{
    auto* B=Board(GetWorld());if(!B)return;float X=0,Y=0;GetOwningPlayerController()->GetMousePosition(X,Y);
    for(int32 I=Buttons.Num()-1;I>=0;--I)if(Buttons[I].Box.IsInside(FVector2D(X,Y)))
    {
        const FName A=Buttons[I].Action;
        if(A==TEXT("Mute"))B->ToggleMute();else if(A==TEXT("Resume"))B->ToggleMenu();else if(A==TEXT("Restart"))B->Restart();else if(A==TEXT("Next"))B->NextLevel();else if(A==TEXT("Revive"))B->Revive();
        break;
    }
}
