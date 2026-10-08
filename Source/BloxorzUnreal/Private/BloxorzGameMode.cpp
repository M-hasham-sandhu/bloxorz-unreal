#include "BloxorzGameMode.h"
#include "BloxorzBoard.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/Canvas.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerInput.h"

ABloxorzGameMode::ABloxorzGameMode(){ PlayerControllerClass=ABloxorzPlayerController::StaticClass(); HUDClass=ABloxorzHUD::StaticClass(); DefaultPawnClass=nullptr; }
void ABloxorzGameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->SpawnActor<ABloxorzBoard>();
    ADirectionalLight* Sun=GetWorld()->SpawnActor<ADirectionalLight>(FVector::ZeroVector,FRotator(-52,-32,0)); Sun->GetLightComponent()->SetIntensity(7.f); Sun->GetLightComponent()->SetLightColor(FLinearColor(.78f,.88f,1.f));
    ASkyLight* Sky=GetWorld()->SpawnActor<ASkyLight>(); Sky->GetLightComponent()->SetIntensity(1.1f); Sky->GetLightComponent()->SetLightColor(FLinearColor(.18f,.25f,.42f));
}

static ABloxorzBoard* Board(UWorld* W){ for(TActorIterator<ABloxorzBoard> It(W);It;++It)return *It; return nullptr; }
void ABloxorzPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent(); bShowMouseCursor=true;
    InputComponent->BindKey(EKeys::W,IE_Pressed,this,&ABloxorzPlayerController::MoveUp); InputComponent->BindKey(EKeys::Up,IE_Pressed,this,&ABloxorzPlayerController::MoveUp);
    InputComponent->BindKey(EKeys::S,IE_Pressed,this,&ABloxorzPlayerController::MoveDown); InputComponent->BindKey(EKeys::Down,IE_Pressed,this,&ABloxorzPlayerController::MoveDown);
    InputComponent->BindKey(EKeys::A,IE_Pressed,this,&ABloxorzPlayerController::MoveLeft); InputComponent->BindKey(EKeys::Left,IE_Pressed,this,&ABloxorzPlayerController::MoveLeft);
    InputComponent->BindKey(EKeys::D,IE_Pressed,this,&ABloxorzPlayerController::MoveRight); InputComponent->BindKey(EKeys::Right,IE_Pressed,this,&ABloxorzPlayerController::MoveRight);
    InputComponent->BindKey(EKeys::R,IE_Pressed,this,&ABloxorzPlayerController::RestartLevel);
}
void ABloxorzPlayerController::MoveUp(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Up);} void ABloxorzPlayerController::MoveDown(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Down);}
void ABloxorzPlayerController::MoveLeft(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Left);} void ABloxorzPlayerController::MoveRight(){if(auto* B=Board(GetWorld()))B->RequestMove(EBloxorzDirection::Right);} void ABloxorzPlayerController::RestartLevel(){if(auto* B=Board(GetWorld()))B->Restart();}
void ABloxorzHUD::DrawHUD()
{
    Super::DrawHUD(); ABloxorzBoard* B=Board(GetWorld()); if(!B||!Canvas)return;
    UFont* Font=GEngine->GetLargeFont(); const FString Moves=FString::Printf(TEXT("MOVES  %02d"),B->GetMoveCount());
    DrawRect(FLinearColor(.02f,.04f,.08f,.72f),24,24,210,54); DrawRect(FLinearColor(.02f,.04f,.08f,.72f),24,Canvas->SizeY-84,520,54);
    DrawText(Moves,FLinearColor(.75f,.9f,1.f),42,38,Font,1.1f,false); DrawText(B->GetStatusText(),B->HasWon()?FLinearColor(.2f,1.f,.65f):FLinearColor(.65f,.72f,.82f),42,Canvas->SizeY-68,Font,.72f,false);
}
