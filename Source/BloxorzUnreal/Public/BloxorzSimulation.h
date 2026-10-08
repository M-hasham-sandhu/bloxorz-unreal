#pragma once

#include "CoreMinimal.h"
#include "BloxorzSimulation.generated.h"

UENUM(BlueprintType)
enum class EBloxorzOrientation : uint8 { Standing, LyingX, LyingY };

UENUM(BlueprintType)
enum class EBloxorzDirection : uint8 { Up, Down, Left, Right };

UENUM(BlueprintType)
enum class EBloxorzTileType : uint8 { Empty, Normal, Fragile, Switch, Bridge, Goal };

UENUM(BlueprintType)
enum class EBloxorzSwitchBehavior : uint8 { Toggle, HeavyOneShot };

USTRUCT(BlueprintType)
struct FBloxorzBlockState
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FIntPoint Anchor = FIntPoint::ZeroValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBloxorzOrientation Orientation = EBloxorzOrientation::Standing;

    FBloxorzBlockState() = default;
    FBloxorzBlockState(FIntPoint InAnchor, EBloxorzOrientation InOrientation) : Anchor(InAnchor), Orientation(InOrientation) {}
    TArray<FIntPoint> OccupiedCells() const;
    bool operator==(const FBloxorzBlockState& Other) const { return Anchor == Other.Anchor && Orientation == Other.Orientation; }
};

USTRUCT(BlueprintType)
struct FBloxorzTile
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FIntPoint Position = FIntPoint::ZeroValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBloxorzTileType Type = EBloxorzTileType::Normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> Targets;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBloxorzSwitchBehavior SwitchBehavior = EBloxorzSwitchBehavior::Toggle;
};

USTRUCT(BlueprintType)
struct FBloxorzLevelData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName LevelId = TEXT("Showcase_01");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FIntPoint GridSize = FIntPoint(7, 8);
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FBloxorzTile> Tiles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FBloxorzBlockState Start;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FIntPoint Goal = FIntPoint::ZeroValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ParMoves = 0;
};

struct FBloxorzLevelState
{
    FBloxorzBlockState Block;
    TMap<FName, int32> Flags;
};

enum class EBloxorzMoveOutcome : uint8 { Valid, Fell };

struct FBloxorzMoveResult
{
    FBloxorzLevelState State;
    EBloxorzMoveOutcome Outcome = EBloxorzMoveOutcome::Fell;
    FBloxorzBlockState AttemptedBlock;
    TArray<FName> ChangedFlags;
};

/** Pure deterministic rules. No actors, animation, physics, or frame-time dependency. */
class BLOXORZUNREAL_API FBloxorzSimulation
{
public:
    static FBloxorzBlockState ApplyRoll(const FBloxorzBlockState& State, EBloxorzDirection Direction);
    static FBloxorzMoveResult ResolveMove(const FBloxorzLevelData& Level, const FBloxorzLevelState& State, EBloxorzDirection Direction);
    static bool IsWin(const FBloxorzLevelData& Level, const FBloxorzLevelState& State);
    static const FBloxorzTile* FindTile(const FBloxorzLevelData& Level, FIntPoint Position);
};
