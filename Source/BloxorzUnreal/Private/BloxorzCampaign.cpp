#include "BloxorzCampaign.h"
TArray<FBloxorzLevelData> MakeBloxorzCampaign()
{
    TArray<FBloxorzLevelData> Campaign;
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_01"); L.GridSize={4,1}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={3,0};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_02"); L.GridSize={6,2}; L.Start.Anchor={0,1}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={3,0};
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_03"); L.GridSize={6,4}; L.Start.Anchor={0,2}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={3,0};
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_04"); L.GridSize={8,5}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={0,3};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_05"); L.GridSize={10,8}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={0,2};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_06"); L.GridSize={5,4}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={4,0};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_07"); L.GridSize={8,8}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={5,5};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,5}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_08"); L.GridSize={8,8}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={7,6};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,6}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_09"); L.GridSize={6,4}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={5,2};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_10"); L.GridSize={5,5}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={1,1};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_11"); L.GridSize={5,4}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={4,3};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw1"); T.Targets={TEXT("sw1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_12"); L.GridSize={5,4}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={4,3};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw1"); T.Targets={TEXT("sw1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_13"); L.GridSize={8,5}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={5,4};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw1"); T.Targets={TEXT("sw1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,4}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,0}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_14"); L.GridSize={7,8}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={0,5};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,3}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw1"); T.Targets={TEXT("sw1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,3}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw2"); T.Targets={TEXT("br1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(1); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,5}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("br1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,6}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,7}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,7}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,6}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,5}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    {
        FBloxorzLevelData L;
        L.LevelId=TEXT("Level_15"); L.GridSize={12,9}; L.Start.Anchor={0,0}; L.Start.Orientation=static_cast<EBloxorzOrientation>(0); L.Goal={0,5};
        { FBloxorzTile T; T.Position={0,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={0,5}; T.Type=static_cast<EBloxorzTileType>(5); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,2}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw2"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={1,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,2}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("sw2"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,3}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,4}; T.Type=static_cast<EBloxorzTileType>(2); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={2,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,2}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw3"); T.Targets={TEXT("br1")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,0}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={6,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={7,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,3}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("br1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={11,3}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,4}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={11,6}; T.Type=static_cast<EBloxorzTileType>(3); T.Id=TEXT("sw2"); T.Targets={TEXT("sw2")}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(1); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={8,2}; T.Type=static_cast<EBloxorzTileType>(4); T.Id=TEXT("br1"); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={3,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={4,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,7}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,6}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={5,5}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={9,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={11,1}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={11,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        { FBloxorzTile T; T.Position={10,2}; T.Type=static_cast<EBloxorzTileType>(1); T.Id=TEXT(""); T.Targets={}; T.SwitchBehavior=static_cast<EBloxorzSwitchBehavior>(0); L.Tiles.Add(T); }
        Campaign.Add(MoveTemp(L));
    }
    return Campaign;
}
