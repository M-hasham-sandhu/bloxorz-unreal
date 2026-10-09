#include "BloxorzGameMode.h"
#include "BloxorzBoard.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/World.h"
#include "EngineUtils.h"

static ABloxorzBoard* Board(UWorld* World){for(TActorIterator<ABloxorzBoard> It(World);It;++It)return *It;return nullptr;}
ABloxorzGameMode::ABloxorzGameMode(){PlayerControllerClass=ABloxorzPlayerController::StaticClass();HUDClass=ABloxorzHUD::StaticClass();DefaultPawnClass=nullptr;}
void ABloxorzGameMode::BeginPlay()
{
    Super::BeginPlay();auto* B=Board(GetWorld());if(!B)B=GetWorld()->SpawnActor<ABloxorzBoard>();
    if(auto* PC=GetWorld()->GetFirstPlayerController()){PC->bAutoManageActiveCameraTarget=false;PC->SetViewTarget(B);}
    int32 Priority=1;
    auto Light=[this,&Priority](FRotator Rotation,float Intensity,FLinearColor Color)
    {
        auto* L=GetWorld()->SpawnActor<ADirectionalLight>(FVector::ZeroVector,Rotation);
        auto* Component=Cast<UDirectionalLightComponent>(L->GetLightComponent());
        Component->SetMobility(EComponentMobility::Movable);Component->SetIntensity(Intensity);Component->SetLightColor(Color);
        Component->SetCastShadows(Priority==1);Component->SetForwardShadingPriority(Priority--);
    };
    Light(FRotator(-55,-35,0),5,FLinearColor(1,.88f,.73f));Light(FRotator(-30,150,0),2,FLinearColor(.40f,.72f,1));
}
void ABloxorzPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();bShowMouseCursor=true;bAutoManageActiveCameraTarget=false;
#define BIND(Key,Action) InputComponent->BindKey(EKeys::Key,IE_Pressed,this,&ABloxorzPlayerController::Action)
    BIND(W,MoveUp);BIND(Up,MoveUp);BIND(S,MoveDown);BIND(Down,MoveDown);
    BIND(A,MoveLeft);BIND(Left,MoveLeft);BIND(D,MoveRight);BIND(Right,MoveRight);
    BIND(R,RestartLevel);BIND(Enter,Confirm);BIND(SpaceBar,Confirm);BIND(Escape,Menu);
    BIND(M,Mute);BIND(PageDown,Next);BIND(PageUp,Previous);BIND(LeftMouseButton,Click);
#undef BIND
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
void ABloxorzPlayerController::Click(){if(auto* HUD=Cast<ABloxorzHUD>(GetHUD()))HUD->HandleClick();}
