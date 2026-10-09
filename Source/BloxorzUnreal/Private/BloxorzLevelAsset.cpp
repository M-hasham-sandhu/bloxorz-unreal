#include "BloxorzLevelAsset.h"

static FString PuzzleStateKey(const FBloxorzLevelState& S)
{
    FString Key=FString::Printf(TEXT("%d,%d,%d"),S.Block.Anchor.X,S.Block.Anchor.Y,int32(S.Block.Orientation));
    TArray<FName> Names; S.Flags.GetKeys(Names); Names.Sort(FNameLexicalLess());
    for(FName Name:Names) if(int32 Value=S.Flags.FindRef(Name)) Key+=FString::Printf(TEXT("|%s=%d"),*Name.ToString(),Value);
    return Key;
}

FBloxorzValidationResult FBloxorzLevelValidator::Validate(const FBloxorzLevelData& L,int32 MaxStates)
{
    FBloxorzValidationResult Result;
    if(L.LevelId.IsNone()) Result.Errors.Add(TEXT("Level ID is required."));
    if(L.GridSize.X<1||L.GridSize.Y<1||L.GridSize.X>64||L.GridSize.Y>64) Result.Errors.Add(TEXT("Grid dimensions must be 1..64."));
    TSet<FIntPoint> Positions; TSet<FName> Bridges,Switches; int32 Goals=0;
    for(const auto& T:L.Tiles)
    {
        if(Positions.Contains(T.Position)) Result.Errors.Add(FString::Printf(TEXT("Duplicate cell (%d,%d)."),T.Position.X,T.Position.Y));
        Positions.Add(T.Position);
        if(T.Position.X<0||T.Position.Y<0||T.Position.X>=L.GridSize.X||T.Position.Y>=L.GridSize.Y) Result.Errors.Add(TEXT("A tile lies outside the grid. Erase it or enlarge the grid."));
        if(T.Type==EBloxorzTileType::Bridge){if(T.Id.IsNone())Result.Errors.Add(TEXT("Bridge requires an ID."));else Bridges.Add(T.Id);}
        if(T.Type==EBloxorzTileType::Switch)
        {
            if(T.Id.IsNone()||Switches.Contains(T.Id)) Result.Errors.Add(TEXT("Independent switches need unique, nonempty IDs."));
            Switches.Add(T.Id);
            if(T.Targets.IsEmpty())Result.Errors.Add(TEXT("Switch has no linked bridge."));
        }
        if(T.Type==EBloxorzTileType::Goal){++Goals;if(T.Position!=L.Goal)Result.Errors.Add(TEXT("Goal tile does not match the goal marker."));}
    }
    if(Goals!=1)Result.Errors.Add(TEXT("Exactly one Goal tile is required."));
    for(const auto& T:L.Tiles)if(T.Type==EBloxorzTileType::Switch)
    {
        TSet<FName> Targets;
        for(FName Target:T.Targets)
        {
            if(!Bridges.Contains(Target))Result.Errors.Add(FString::Printf(TEXT("Missing bridge target: %s."),*Target.ToString()));
            if(Targets.Contains(Target))Result.Errors.Add(TEXT("Duplicate target would toggle a bridge twice."));
            Targets.Add(Target);
        }
        if(Bridges.Contains(T.Id))Result.Warnings.Add(TEXT("Legacy shared switch/bridge ID is supported; distinct IDs are clearer for new puzzles."));
    }
    for(auto Cell:L.Start.OccupiedCells())
    {
        const auto* T=FBloxorzSimulation::FindTile(L,Cell);
        if(!T||T->Type==EBloxorzTileType::Bridge||(T->Type==EBloxorzTileType::Fragile&&L.Start.Orientation==EBloxorzOrientation::Standing))Result.Errors.Add(TEXT("Start pose lacks valid initial support."));
    }
    if(!Result.Errors.IsEmpty())return Result;
    struct FNode{FBloxorzLevelState State; int32 Parent; TCHAR Direction;};
    FBloxorzLevelState Initial; Initial.Block=L.Start;
    TArray<FNode> Queue; Queue.Add({Initial,INDEX_NONE,0});
    TSet<FString> Seen; Seen.Add(PuzzleStateKey(Initial));
    MaxStates=FMath::Max(1,MaxStates);
    for(int32 Head=0;Head<Queue.Num();++Head)
    {
        const FBloxorzLevelState Current=Queue[Head].State; ++Result.Explored;
        if(FBloxorzSimulation::IsWin(L,Current))
        {
            Result.bSolved=true;
            for(int32 Node=Head;Queue[Node].Parent!=INDEX_NONE;Node=Queue[Node].Parent)Result.Solution.InsertAt(0,Queue[Node].Direction);
            return Result;
        }
        for(int32 D=0;D<4;++D)
        {
            const auto Move=FBloxorzSimulation::ResolveMove(L,Current,static_cast<EBloxorzDirection>(D));
            if(Move.Outcome!=EBloxorzMoveOutcome::Valid)continue;
            FString Key=PuzzleStateKey(Move.State); if(Seen.Contains(Key))continue;
            if(Queue.Num()>=MaxStates){Result.bLimitReached=true;return Result;}
            Seen.Add(Key);Queue.Add({Move.State,Head,TEXT("UDLR")[D]});
        }
    }
    return Result;
}
