#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "BloxorzGameMode.generated.h"

UCLASS() class BLOXORZUNREAL_API ABloxorzPlayerController : public APlayerController
{
    GENERATED_BODY()
protected:
    virtual void SetupInputComponent() override;
private:
    void MoveUp(); void MoveDown(); void MoveLeft(); void MoveRight(); void RestartLevel();
    void Confirm(); void Menu(); void Mute(); void Next(); void Previous(); void Click();
};

UCLASS() class BLOXORZUNREAL_API ABloxorzHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;
    void HandleClick();
private:
    struct FButton { FBox2D Box; FName Action; };
    TArray<FButton> Buttons;
};

UCLASS() class BLOXORZUNREAL_API ABloxorzGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ABloxorzGameMode();
    virtual void BeginPlay() override;
};
