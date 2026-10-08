#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloxorzSimulation.h"
#include "BloxorzBoard.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UTextRenderComponent;

UCLASS(Blueprintable)
class BLOXORZUNREAL_API ABloxorzBoard : public AActor
{
    GENERATED_BODY()
public:
    ABloxorzBoard();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bloxorz|Level") FBloxorzLevelData Level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bloxorz|Presentation") float CellSize = 120.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bloxorz|Presentation") float RollDuration = .22f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bloxorz|Presentation") float FallDuration = .8f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bloxorz|Presentation") float CameraShakeStrength = 1.8f;

    UFUNCTION(BlueprintCallable) void RequestMove(EBloxorzDirection Direction);
    UFUNCTION(BlueprintCallable) void Restart();
    UFUNCTION(BlueprintPure) int32 GetMoveCount() const { return MoveCount; }
    UFUNCTION(BlueprintPure) bool IsBusy() const { return Phase != EPhase::Idle; }
    UFUNCTION(BlueprintPure) bool HasWon() const { return bWon; }
    UFUNCTION(BlueprintPure) FString GetStatusText() const;

private:
    enum class EPhase : uint8 { Idle, Rolling, Falling, Completing };
    UPROPERTY() TObjectPtr<USceneComponent> SceneRoot;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> NormalTiles;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> FragileTiles;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> SwitchTiles;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> BridgeTiles;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> GoalTiles;
    UPROPERTY() TObjectPtr<UStaticMeshComponent> BlockMesh;
    UPROPERTY() TObjectPtr<UCameraComponent> Camera;
    UPROPERTY() TObjectPtr<UTextRenderComponent> TitleText;

    FBloxorzLevelState State;
    FBloxorzLevelState LastValidState;
    FBloxorzBlockState AnimFrom;
    FBloxorzBlockState AnimTo;
    EBloxorzDirection AnimDirection = EBloxorzDirection::Up;
    EPhase Phase = EPhase::Idle;
    float PhaseTime = 0.f;
    int32 MoveCount = 0;
    bool bWon = false;

    void BuildShowcaseLevel();
    void BuildBoardVisuals();
    void RefreshBridgeVisuals();
    FVector BlockCenter(const FBloxorzBlockState& Block) const;
    FQuat BlockRotation(const FBloxorzBlockState& Block) const;
    void SnapBlock(const FBloxorzBlockState& Block);
    void FinishFall();
};
