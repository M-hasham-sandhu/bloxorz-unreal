#include "BloxorzSimulation.h"

TArray<FIntPoint> FBloxorzBlockState::OccupiedCells() const
{
    TArray<FIntPoint> Cells{Anchor};
    if (Orientation == EBloxorzOrientation::LyingX) Cells.Add(Anchor + FIntPoint(1, 0));
    else if (Orientation == EBloxorzOrientation::LyingY) Cells.Add(Anchor + FIntPoint(0, 1));
    return Cells;
}

FBloxorzBlockState FBloxorzSimulation::ApplyRoll(const FBloxorzBlockState& S, EBloxorzDirection D)
{
    const FIntPoint A = S.Anchor;
    if (S.Orientation == EBloxorzOrientation::Standing)
    {
        if (D == EBloxorzDirection::Right) return {A + FIntPoint(1,0), EBloxorzOrientation::LyingX};
        if (D == EBloxorzDirection::Left)  return {A + FIntPoint(-2,0), EBloxorzOrientation::LyingX};
        if (D == EBloxorzDirection::Up)    return {A + FIntPoint(0,1), EBloxorzOrientation::LyingY};
        return {A + FIntPoint(0,-2), EBloxorzOrientation::LyingY};
    }
    if (S.Orientation == EBloxorzOrientation::LyingX)
    {
        if (D == EBloxorzDirection::Right) return {A + FIntPoint(2,0), EBloxorzOrientation::Standing};
        if (D == EBloxorzDirection::Left)  return {A + FIntPoint(-1,0), EBloxorzOrientation::Standing};
        if (D == EBloxorzDirection::Up)    return {A + FIntPoint(0,1), EBloxorzOrientation::LyingX};
        return {A + FIntPoint(0,-1), EBloxorzOrientation::LyingX};
    }
    if (D == EBloxorzDirection::Right) return {A + FIntPoint(1,0), EBloxorzOrientation::LyingY};
    if (D == EBloxorzDirection::Left)  return {A + FIntPoint(-1,0), EBloxorzOrientation::LyingY};
    if (D == EBloxorzDirection::Up)    return {A + FIntPoint(0,2), EBloxorzOrientation::Standing};
    return {A + FIntPoint(0,-1), EBloxorzOrientation::Standing};
}

const FBloxorzTile* FBloxorzSimulation::FindTile(const FBloxorzLevelData& Level, FIntPoint P)
{
    return Level.Tiles.FindByPredicate([P](const FBloxorzTile& T){ return T.Position == P && T.Type != EBloxorzTileType::Empty; });
}

FBloxorzMoveResult FBloxorzSimulation::ResolveMove(const FBloxorzLevelData& Level, const FBloxorzLevelState& Current, EBloxorzDirection Direction)
{
    FBloxorzMoveResult Result;
    Result.State = Current;
    Result.AttemptedBlock = ApplyRoll(Current.Block, Direction);
    for (const FIntPoint Cell : Result.AttemptedBlock.OccupiedCells())
    {
        const FBloxorzTile* Tile = FindTile(Level, Cell);
        if (!Tile) return Result;
        if (Tile->Type == EBloxorzTileType::Fragile && Result.AttemptedBlock.Orientation == EBloxorzOrientation::Standing) return Result;
        if (Tile->Type == EBloxorzTileType::Bridge && (Tile->Id.IsNone() || Current.Flags.FindRef(Tile->Id) == 0)) return Result;
    }

    Result.Outcome = EBloxorzMoveOutcome::Valid;
    Result.State.Block = Result.AttemptedBlock;
    for (const FIntPoint Cell : Result.State.Block.OccupiedCells())
    {
        const FBloxorzTile* Tile = FindTile(Level, Cell);
        if (!Tile || Tile->Type != EBloxorzTileType::Switch) continue;
        if (Tile->SwitchBehavior == EBloxorzSwitchBehavior::HeavyOneShot)
        {
            if (Result.State.Block.Orientation != EBloxorzOrientation::Standing) continue;
            const FName TriggerKey(*FString::Printf(TEXT("switch:%s:%d,%d"), *Tile->Id.ToString(), Cell.X, Cell.Y));
            if (Result.State.Flags.FindRef(TriggerKey) != 0) continue;
            Result.State.Flags.Add(TriggerKey, 1);
        }
        for (const FName Target : Tile->Targets)
        {
            if (Target.IsNone()) continue;
            Result.State.Flags.Add(Target, Result.State.Flags.FindRef(Target) == 0 ? 1 : 0);
            Result.ChangedFlags.AddUnique(Target);
        }
    }
    return Result;
}

bool FBloxorzSimulation::IsWin(const FBloxorzLevelData& Level, const FBloxorzLevelState& State)
{
    return State.Block.Orientation == EBloxorzOrientation::Standing && State.Block.Anchor == Level.Goal;
}
