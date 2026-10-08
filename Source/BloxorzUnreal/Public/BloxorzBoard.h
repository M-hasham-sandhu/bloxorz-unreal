#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SaveGame.h"
#include "BloxorzSimulation.h"
#include "BloxorzBoard.generated.h"
class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UNiagaraSystem;
class USoundWave;
UCLASS()
class UBloxorzProgress : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY() int32 Unlocked = 0;
    UPROPERTY() TMap<int32,int32> BestMoves;
};
UCLASS(Blueprintable)
class BLOXORZUNREAL_API ABloxorzBoard : public AActor
{
    GENERATED_BODY()
public:
    ABloxorzBoard();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level") FBloxorzLevelData Level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation", meta=(ClampMin="10")) float CellSize = 120.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation", meta=(ClampMin="0.08")) float RollDuration = .21f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation") float FallDuration = .75f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation") float CameraShakeStrength = 1.1f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation") TObjectPtr<UNiagaraSystem> LandingEffect;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Presentation") TObjectPtr<UNiagaraSystem> CompletionEffect;
    UFUNCTION(BlueprintCallable) void RequestMove(EBloxorzDirection Direction);
    UFUNCTION(BlueprintCallable) void Restart();
    UFUNCTION(BlueprintCallable) void Revive();
    UFUNCTION(BlueprintCallable) void NextLevel();
    UFUNCTION(BlueprintCallable) void PreviousLevel();
    UFUNCTION(BlueprintCallable) void ToggleMenu();
    UFUNCTION(BlueprintCallable) void ToggleMute();
    UFUNCTION(BlueprintCallable) void LoadLevel(int32 Index);
    UFUNCTION(BlueprintPure) int32 GetMoveCount() const { return MoveCount; }
    UFUNCTION(BlueprintPure) bool HasWon() const { return Phase == EPhase::Complete; }
    UFUNCTION(BlueprintPure) bool IsBusy() const { return Phase != EPhase::Idle; }
    UFUNCTION(BlueprintPure) FString GetStatusText() const;
    int32 GetLevelIndex() const { return LevelIndex; }
    int32 GetLevelCount() const { return Campaign.Num(); }
    int32 GetRevives() const { return Revives; }
    int32 GetBest() const { return Progress ? Progress->BestMoves.FindRef(LevelIndex) : 0; }
    bool IsMenuOpen() const { return bMenu; }
    bool IsDead() const { return Phase==EPhase::Failed; }
    bool IsMuted() const { return bMuted; }
    static FVector LogicalCenter(const FBloxorzBlockState& Block, float Cell);
    static FVector RollDirection(EBloxorzDirection Direction);
    static FVector RollPivot(const FBloxorzBlockState& Block, EBloxorzDirection Direction, float Cell);
private:
    enum class EPhase : uint8 { Idle, Rolling, Falling, Failed, Completing, Complete };
    struct FTileVisual { int32 Tile=0; int32 Body=0; int32 Cap=0; float Open=1; };
    struct FParticle { FVector Start; FVector Velocity; float Age=0; float Life=1; float Size=1; };
    UPROPERTY() TObjectPtr<USceneComponent> SceneRoot;
    UPROPERTY() TObjectPtr<UStaticMeshComponent> BlockMesh;
    UPROPERTY() TObjectPtr<UCameraComponent> Camera;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> Bodies;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> Caps;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> Marks;
    UPROPERTY() TObjectPtr<UInstancedStaticMeshComponent> Sparks;
    UPROPERTY() TObjectPtr<UStaticMeshComponent> Ground;
    UPROPERTY() TObjectPtr<UBloxorzProgress> Progress;
    UPROPERTY() TArray<TObjectPtr<USoundWave>> Sounds;
    TArray<FBloxorzLevelData> Campaign;
    TArray<FTileVisual> TileVisuals;
    TArray<FParticle> Particles;
    FBloxorzLevelState State;
    FBloxorzMoveResult Pending;
    FBloxorzBlockState AnimFrom;
    FQuat StartRotation;
    FVector Pivot, Axis, CameraHome, BoardCenter, BoundsMin, BoundsMax;
    float PhaseTime=0, LandingAge=10, Elapsed=0, BufferAge=0, LastAspect=0;
    int32 MoveCount=0, LevelIndex=0, Revives=3;
    bool bWon=false, bMenu=false, bMuted=false, bBuffered=false, bSmoke=false;
    EBloxorzDirection BufferedDirection=EBloxorzDirection::Up;
    EPhase Phase=EPhase::Idle;
    FString ReplayPath;
    int32 ReplayIndex=0;
    bool bReplay=false;
    bool bProfile=false;
    TArray<float> ProfileFrameTimes;
    double ReplayFrameTotal=0;
    int32 ReplayFrames=0;
    void BuildVisuals();
    void UpdateTiles(float Dt, bool bSnap=false);
    void FitCamera();
    void SnapBlock();
    void Burst(FVector Position, int32 Count, float Speed);
    void PlayFeedback(int32 Index, float Volume=1);
    void FinishRoll();
    void SaveProgress();
};
