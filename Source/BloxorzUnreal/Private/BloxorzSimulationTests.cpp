#if WITH_DEV_AUTOMATION_TESTS
#include "BloxorzSimulation.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBloxorzRollTableTest,"Bloxorz.Simulation.RollTable",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBloxorzRollTableTest::RunTest(const FString&)
{
    const FIntPoint A(5,5);
    struct FCase{EBloxorzOrientation O;EBloxorzDirection D;FIntPoint P;EBloxorzOrientation Out;};
    const FCase Cases[]={{EBloxorzOrientation::Standing,EBloxorzDirection::Right,{6,5},EBloxorzOrientation::LyingX},{EBloxorzOrientation::Standing,EBloxorzDirection::Left,{3,5},EBloxorzOrientation::LyingX},{EBloxorzOrientation::Standing,EBloxorzDirection::Up,{5,6},EBloxorzOrientation::LyingY},{EBloxorzOrientation::Standing,EBloxorzDirection::Down,{5,3},EBloxorzOrientation::LyingY},{EBloxorzOrientation::LyingX,EBloxorzDirection::Right,{7,5},EBloxorzOrientation::Standing},{EBloxorzOrientation::LyingX,EBloxorzDirection::Left,{4,5},EBloxorzOrientation::Standing},{EBloxorzOrientation::LyingX,EBloxorzDirection::Up,{5,6},EBloxorzOrientation::LyingX},{EBloxorzOrientation::LyingX,EBloxorzDirection::Down,{5,4},EBloxorzOrientation::LyingX},{EBloxorzOrientation::LyingY,EBloxorzDirection::Right,{6,5},EBloxorzOrientation::LyingY},{EBloxorzOrientation::LyingY,EBloxorzDirection::Left,{4,5},EBloxorzOrientation::LyingY},{EBloxorzOrientation::LyingY,EBloxorzDirection::Up,{5,7},EBloxorzOrientation::Standing},{EBloxorzOrientation::LyingY,EBloxorzDirection::Down,{5,4},EBloxorzOrientation::Standing}};
    for(const FCase& C:Cases){const FBloxorzBlockState R=FBloxorzSimulation::ApplyRoll({A,C.O},C.D); TestTrue(TEXT("anchor"),R.Anchor==C.P); TestEqual(TEXT("orientation"),R.Orientation,C.Out);} return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBloxorzRulesTest,"Bloxorz.Simulation.TileRules",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBloxorzRulesTest::RunTest(const FString&)
{
    FBloxorzLevelData L; L.Start={FIntPoint(0,0),EBloxorzOrientation::Standing};
    auto Add=[&](int X,int Y,EBloxorzTileType Type,FName Id=NAME_None,TArray<FName> Targets={}){FBloxorzTile T;T.Position={X,Y};T.Type=Type;T.Id=Id;T.Targets=Targets;L.Tiles.Add(T);};
    Add(0,0,EBloxorzTileType::Normal); Add(1,0,EBloxorzTileType::Normal); Add(2,0,EBloxorzTileType::Normal);
    Add(3,0,EBloxorzTileType::Switch,TEXT("s"),{TEXT("b")}); Add(4,0,EBloxorzTileType::Bridge,TEXT("b")); Add(5,0,EBloxorzTileType::Normal);
    FBloxorzLevelState S;S.Block=L.Start; auto R=FBloxorzSimulation::ResolveMove(L,S,EBloxorzDirection::Right); TestEqual(TEXT("first roll valid"),R.Outcome,EBloxorzMoveOutcome::Valid);
    R=FBloxorzSimulation::ResolveMove(L,R.State,EBloxorzDirection::Right); TestEqual(TEXT("switch landing valid"),R.Outcome,EBloxorzMoveOutcome::Valid); TestEqual(TEXT("bridge toggled"),R.State.Flags.FindRef(TEXT("b")),1);
    R=FBloxorzSimulation::ResolveMove(L,R.State,EBloxorzDirection::Right); TestEqual(TEXT("open bridge supports"),R.Outcome,EBloxorzMoveOutcome::Valid);
    FBloxorzLevelData F; FBloxorzTile Frag;Frag.Position={0,0};Frag.Type=EBloxorzTileType::Fragile;F.Tiles.Add(Frag); FBloxorzLevelState Upright;Upright.Block={{0,-2},EBloxorzOrientation::LyingY}; auto Fall=FBloxorzSimulation::ResolveMove(F,Upright,EBloxorzDirection::Up);TestEqual(TEXT("upright breaks fragile"),Fall.Outcome,EBloxorzMoveOutcome::Fell); return true;
}
#endif
