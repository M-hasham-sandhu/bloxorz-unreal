#pragma once
#include "Engine/DataAsset.h"
#include "BloxorzSimulation.h"
#include "BloxorzLevelAsset.generated.h"

/** Designer-owned puzzle. No presentation objects or simulation state are serialized. */
UCLASS(BlueprintType)
class BLOXORZUNREAL_API UBloxorzLevelAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle") FBloxorzLevelData Data;
};

/** Ordered, soft-referenced campaign. Levels may be reordered without rebuilding code. */
UCLASS(BlueprintType)
class BLOXORZUNREAL_API UBloxorzCampaignAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Campaign") TArray<TSoftObjectPtr<UBloxorzLevelAsset>> Levels;
};

struct BLOXORZUNREAL_API FBloxorzValidationResult
{
    TArray<FString> Errors;
    TArray<FString> Warnings;
    FString Solution;
    int32 Explored=0;
    bool bSolved=false;
    bool bLimitReached=false;
};

/** Shared authoring validation; a bounded search never reports budget exhaustion as unsolvable. */
class BLOXORZUNREAL_API FBloxorzLevelValidator
{
public:
    static FBloxorzValidationResult Validate(const FBloxorzLevelData& Level, int32 MaxStates=100000);
};
