#include "BloxorzCampaign.h"
#include "BloxorzLevelAsset.h"

TArray<FBloxorzLevelData> MakeBloxorzCampaign()
{
    TArray<FBloxorzLevelData> Result;
    const auto* Campaign=LoadObject<UBloxorzCampaignAsset>(nullptr,TEXT("/Game/Levels/DA_Campaign.DA_Campaign"));
    if(!Campaign)return Result;
    for(const auto& Reference:Campaign->Levels)
    {
        if(const auto* Level=Reference.LoadSynchronous())Result.Add(Level->Data);
        else UE_LOG(LogTemp,Error,TEXT("Campaign contains a missing puzzle: %s"),*Reference.ToString());
    }
    return Result;
}
