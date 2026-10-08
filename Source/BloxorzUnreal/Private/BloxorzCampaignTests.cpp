#if WITH_DEV_AUTOMATION_TESTS
#include "BloxorzSimulation.h"
#include "BloxorzCampaign.h"
#include "BloxorzBoard.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBloxorzPivotTest,"Bloxorz.Presentation.PivotEndpoints",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBloxorzPivotTest::RunTest(const FString&)
{
    for(int O=0;O<3;++O)for(int D=0;D<4;++D)
    {
        const FBloxorzBlockState Start({4,4},static_cast<EBloxorzOrientation>(O));
        const auto Dir=static_cast<EBloxorzDirection>(D);
        const auto Next=FBloxorzSimulation::ApplyRoll(Start,Dir);
        const FVector P=ABloxorzBoard::RollPivot(Start,Dir,120);
        const FQuat Q(FVector::CrossProduct(FVector::UpVector,ABloxorzBoard::RollDirection(Dir)),PI*.5f);
        const FVector End=P+Q.RotateVector(ABloxorzBoard::LogicalCenter(Start,120)-P);
        TestTrue(TEXT("Quarter-turn pivot ends at exact grid center"),End.Equals(ABloxorzBoard::LogicalCenter(Next,120),.001f));
    }
    return true;
}
static FString StateKey(const FBloxorzLevelState& S)
{
    FString K=FString::Printf(TEXT("%d,%d,%d"),S.Block.Anchor.X,S.Block.Anchor.Y,int32(S.Block.Orientation));
    TArray<FName> Keys;S.Flags.GetKeys(Keys);Keys.Sort(FNameLexicalLess());
    for(const FName N:Keys)if(S.Flags.FindRef(N)!=0)K+=TEXT("|")+N.ToString();
    return K;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBloxorzCampaignTest,"Bloxorz.Campaign.AllLevelsSolvable",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBloxorzCampaignTest::RunTest(const FString&)
{
    auto Campaign=MakeBloxorzCampaign();TestEqual(TEXT("15 reference levels"),Campaign.Num(),15);
    for(const auto& L:Campaign)
    {
        struct FNode{FBloxorzLevelState S;FString Path;};
        TArray<FNode> Queue;FBloxorzLevelState S;S.Block=L.Start;Queue.Add({S,TEXT("")});
        TSet<FString> Seen;Seen.Add(StateKey(S));bool Solved=false;
        for(int Head=0;Head<Queue.Num()&&Head<100000;++Head)
        {
            const FNode Node=Queue[Head];
            if(FBloxorzSimulation::IsWin(L,Node.S)){Solved=true;AddInfo(FString::Printf(TEXT("%s: shortest=%d path=%s explored=%d"),*L.LevelId.ToString(),Node.Path.Len(),*Node.Path,Head+1));break;}
            for(int D=0;D<4;++D)
            {
                const auto R=FBloxorzSimulation::ResolveMove(L,Node.S,static_cast<EBloxorzDirection>(D));
                if(R.Outcome!=EBloxorzMoveOutcome::Valid)continue;
                const FString K=StateKey(R.State);if(Seen.Contains(K))continue;
                Seen.Add(K);Queue.Add({R.State,Node.Path+FString::Chr(TEXT("UDLR")[D])});
            }
        }
        TestTrue(*FString::Printf(TEXT("%s is solvable"),*L.LevelId.ToString()),Solved);
    }
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBloxorzHeavyTest,"Bloxorz.Simulation.HeavySwitchAndSupportOrder",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBloxorzHeavyTest::RunTest(const FString&)
{
    FBloxorzLevelData L;L.GridSize={10,10};
    for(int X=0;X<10;++X)for(int Y=0;Y<10;++Y){FBloxorzTile T;T.Position={X,Y};L.Tiles.Add(T);}
    auto* Switch=L.Tiles.FindByPredicate([](const auto& T){return T.Position==FIntPoint(3,3);});
    Switch->Type=EBloxorzTileType::Switch;Switch->Id=TEXT("heavy");Switch->Targets={TEXT("bridge")};Switch->SwitchBehavior=EBloxorzSwitchBehavior::HeavyOneShot;
    FBloxorzLevelState S;S.Block={{1,3},EBloxorzOrientation::LyingX};
    auto R=FBloxorzSimulation::ResolveMove(L,S,EBloxorzDirection::Right);
    TestEqual(TEXT("Heavy upright fires"),R.State.Flags.FindRef(TEXT("bridge")),1);
    auto Away=FBloxorzSimulation::ResolveMove(L,R.State,EBloxorzDirection::Left);
    auto Back=FBloxorzSimulation::ResolveMove(L,Away.State,EBloxorzDirection::Right);
    TestEqual(TEXT("Heavy switch cannot toggle twice"),Back.State.Flags.FindRef(TEXT("bridge")),1);
    TestEqual(TEXT("Input state unmodified"),S.Flags.Num(),0);
    S.Block={{2,2},EBloxorzOrientation::LyingX};
    auto Flat=FBloxorzSimulation::ResolveMove(L,S,EBloxorzDirection::Up);
    TestEqual(TEXT("Heavy ignores flat landing"),Flat.State.Flags.FindRef(TEXT("bridge")),0);
    auto* Bridge=L.Tiles.FindByPredicate([](const auto& T){return T.Position==FIntPoint(2,3);});
    Bridge->Type=EBloxorzTileType::Bridge;Bridge->Id=TEXT("bridge");
    Switch->SwitchBehavior=EBloxorzSwitchBehavior::Toggle;
    auto Failed=FBloxorzSimulation::ResolveMove(L,S,EBloxorzDirection::Up);
    TestEqual(TEXT("Closed support is checked before switch effects"),Failed.Outcome,EBloxorzMoveOutcome::Fell);
    TestEqual(TEXT("Fall preserves flags"),Failed.State.Flags.Num(),0);
    L.Goal={3,3};TestTrue(TEXT("Standing goal wins"),FBloxorzSimulation::IsWin(L,R.State));
    TestFalse(TEXT("Flat over goal does not win"),FBloxorzSimulation::IsWin(L,Flat.State));
    return true;
}
#endif
