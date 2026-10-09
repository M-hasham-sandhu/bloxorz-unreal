#include "Modules/ModuleManager.h"
#include "BloxorzLevelAsset.h"
#include "ToolMenus.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "AssetToolsModule.h"
#include "Factories/DataAssetFactory.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "PropertyCustomizationHelpers.h"
#include "ScopedTransaction.h"
#include "FileHelpers.h"
#include "Editor.h"
#include "EditorUndoClient.h"
#include "PlayInEditorDataTypes.h"
#include "UObject/StrongObjectPtr.h"
#include "Misc/PackageName.h"
#include "HAL/IConsoleManager.h"
#include "Misc/AutomationTest.h"

namespace BloxorzDesigner
{
static const FName TabId(TEXT("BloxorzLevelDesigner"));
enum class EBrush : uint8 { Normal, Empty, Fragile, Switch, Bridge, Start, Goal, Link };

class SGrid : public SLeafWidget
{
public:
    SLATE_BEGIN_ARGS(SGrid){} SLATE_END_ARGS()
    TFunction<UBloxorzLevelAsset*()> Asset;
    TFunction<void(FIntPoint)> Edit;
    TFunction<bool()> CanDrag;
    TUniquePtr<FScopedTransaction> Transaction;
    FIntPoint LastCell=FIntPoint(-1,-1);
    void Construct(const FArguments&){}
    FVector2D ComputeDesiredSize(float) const override
    {
        const auto* A=Asset?Asset():nullptr;
        return A?FVector2D(FMath::Clamp(A->Data.GridSize.X,1,64)*48,FMath::Clamp(A->Data.GridSize.Y,1,64)*48):FVector2D(400,300);
    }
    int32 OnPaint(const FPaintArgs&,const FGeometry& G,const FSlateRect&,FSlateWindowElementList& Out,int32 Layer,const FWidgetStyle&,bool) const override
    {
        const auto* A=Asset?Asset():nullptr;if(!A)return Layer;
        const auto& D=A->Data;const int32 W=FMath::Clamp(D.GridSize.X,1,64),H=FMath::Clamp(D.GridSize.Y,1,64);
        const auto Font=FCoreStyle::GetDefaultFontStyle("Regular",10);
        for(int32 Y=0;Y<H;++Y)for(int32 X=0;X<W;++X)
        {
            const FIntPoint Cell(X,Y);const auto* T=FBloxorzSimulation::FindTile(D,Cell);
            FLinearColor Color(.035f,.05f,.065f);FString Label=FString::Printf(TEXT("%d,%d"),X,Y);
            if(T)switch(T->Type)
            {
                case EBloxorzTileType::Normal:Color=FLinearColor(.16f,.26f,.30f);break;
                case EBloxorzTileType::Fragile:Color=FLinearColor(.42f,.28f,.12f);Label+=TEXT(" F");break;
                case EBloxorzTileType::Switch:Color=FLinearColor(.04f,.40f,.43f);Label+=T->SwitchBehavior==EBloxorzSwitchBehavior::Toggle?TEXT(" A"):TEXT(" B");break;
                case EBloxorzTileType::Bridge:Color=FLinearColor(.50f,.34f,.10f);Label+=TEXT(" BR");break;
                case EBloxorzTileType::Goal:Color=FLinearColor(.08f,.48f,.24f);Label+=TEXT(" G");break;
                default:break;
            }
            if(D.Start.Anchor==Cell)Label+=TEXT(" S");
            const FVector2D P(X*48,(H-1-Y)*48);
            FSlateDrawElement::MakeBox(Out,Layer,G.ToPaintGeometry(FVector2D(46,46),FSlateLayoutTransform(P)),FCoreStyle::Get().GetBrush("WhiteBrush"),ESlateDrawEffect::None,Color);
            FSlateDrawElement::MakeText(Out,Layer+1,G.ToPaintGeometry(FVector2D(46,46),FSlateLayoutTransform(P+FVector2D(2,5))),Label,Font,ESlateDrawEffect::None,FLinearColor::White);
            if(T&&!T->Id.IsNone())FSlateDrawElement::MakeText(Out,Layer+1,G.ToPaintGeometry(FVector2D(46,46),FSlateLayoutTransform(P+FVector2D(2,25))),T->Id.ToString().Left(7),Font,ESlateDrawEffect::None,FLinearColor(.8f,.9f,.9f));
        }
        return Layer+1;
    }
    void PaintAt(const FGeometry& G,const FPointerEvent& Event)
    {
        auto* A=Asset?Asset():nullptr;if(!A)return;
        const FVector2D P=G.AbsoluteToLocal(Event.GetScreenSpacePosition());
        const FIntPoint Cell(FMath::FloorToInt(P.X/48),A->Data.GridSize.Y-1-FMath::FloorToInt(P.Y/48));
        if(Cell.X<0||Cell.Y<0||Cell.X>=A->Data.GridSize.X||Cell.Y>=A->Data.GridSize.Y||Cell==LastCell)return;
        LastCell=Cell;Edit(Cell);Invalidate(EInvalidateWidgetReason::Paint);
    }
    FReply OnMouseButtonDown(const FGeometry& G,const FPointerEvent& Event) override
    {
        if(Event.GetEffectingButton()!=EKeys::LeftMouseButton||!Asset||!Asset())return FReply::Unhandled();
        Transaction=MakeUnique<FScopedTransaction>(FText::FromString(TEXT("Paint Bloxorz puzzle")));Asset()->Modify();LastCell=FIntPoint(-1,-1);PaintAt(G,Event);
        return FReply::Handled().CaptureMouse(SharedThis(this));
    }
    FReply OnMouseMove(const FGeometry& G,const FPointerEvent& Event) override
    {
        if(HasMouseCapture()&&Event.IsMouseButtonDown(EKeys::LeftMouseButton)&&(!CanDrag||CanDrag())){PaintAt(G,Event);return FReply::Handled();}return FReply::Unhandled();
    }
    FReply OnMouseButtonUp(const FGeometry&,const FPointerEvent& Event) override
    {
        if(Event.GetEffectingButton()==EKeys::LeftMouseButton&&HasMouseCapture()){Transaction.Reset();return FReply::Handled().ReleaseMouseCapture();}return FReply::Unhandled();
    }
    void OnMouseCaptureLost(const FCaptureLostEvent&) override {Transaction.Reset();}
};

class SDesigner : public SCompoundWidget, public FEditorUndoClient
{
public:
    SLATE_BEGIN_ARGS(SDesigner){} SLATE_END_ARGS()
    TStrongObjectPtr<UBloxorzLevelAsset> Selected;
    TStrongObjectPtr<UBloxorzCampaignAsset> Campaign;
    TSharedPtr<IDetailsView> Details;
    TSharedPtr<SGrid> Grid;
    TArray<TSharedPtr<FString>> Brushes;
    EBrush Brush=EBrush::Normal;
    FString Id=TEXT("sw1"),Status=TEXT("Create or select a puzzle. Paint by dragging; links use two separate clicks.");
    bool bHeavy=false;
    FIntPoint LinkCell=FIntPoint(-1,-1);
    ~SDesigner(){if(GEditor)GEditor->UnregisterForUndo(this);}
    void RefreshGrid(const FPropertyChangedEvent&){if(Grid.IsValid())Grid->Invalidate(EInvalidateWidgetReason::Layout);}
    void PostUndo(bool) override {if(Grid.IsValid())Grid->Invalidate(EInvalidateWidgetReason::Layout);if(Details.IsValid())Details->ForceRefresh();}
    void PostRedo(bool Success) override {PostUndo(Success);}
    void Construct(const FArguments&)
    {
        Campaign.Reset(LoadObject<UBloxorzCampaignAsset>(nullptr,TEXT("/Game/Levels/DA_Campaign.DA_Campaign")));
        if(Campaign.IsValid()&&!Campaign->Levels.IsEmpty())Selected.Reset(Campaign->Levels[0].LoadSynchronous());
        FDetailsViewArgs Args;Args.bHideSelectionTip=true;Args.bAllowSearch=true;
        Details=FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(Args);Details->SetObject(Selected.Get());
        for(const TCHAR* Name:{TEXT("Normal"),TEXT("Erase"),TEXT("Fragile"),TEXT("Switch"),TEXT("Bridge"),TEXT("Start"),TEXT("Goal"),TEXT("Link")})Brushes.Add(MakeShared<FString>(Name));
        Grid=SNew(SGrid);Grid->Asset=[this](){return Selected.Get();};Grid->Edit=[this](FIntPoint Cell){Paint(Cell);};
        Grid->CanDrag=[this](){return int32(Brush)<=int32(EBrush::Bridge);};
        Details->OnFinishedChangingProperties().AddSP(this,&SDesigner::RefreshGrid);
        GEditor->RegisterForUndo(this);
        ChildSlot[SNew(SVerticalBox)
            +SVerticalBox::Slot().AutoHeight()[SNew(SHorizontalBox)
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("New puzzle")).OnClicked_Lambda([this](){return Create();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Save")).OnClicked_Lambda([this](){return Save();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Validate / solve")).OnClicked_Lambda([this](){return Validate();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Play selected")).OnClicked_Lambda([this](){return Play();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Add to campaign")).OnClicked_Lambda([this](){return AddToCampaign();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Campaign order")).OnClicked_Lambda([this](){Details->SetObject(Campaign.Get());return FReply::Handled();})]
            ]
            +SVerticalBox::Slot().AutoHeight()[SNew(SObjectPropertyEntryBox).AllowedClass(UBloxorzLevelAsset::StaticClass())
                .ObjectPath_Lambda([this](){return Selected.IsValid()?Selected->GetPathName():FString();})
                .OnObjectChanged_Lambda([this](const FAssetData& Data){Selected.Reset(Cast<UBloxorzLevelAsset>(Data.GetAsset()));LinkCell=FIntPoint(-1,-1);Details->SetObject(Selected.Get());Grid->Invalidate(EInvalidateWidgetReason::Layout);})]
            +SVerticalBox::Slot().AutoHeight()[SNew(SHorizontalBox)
                +SHorizontalBox::Slot().AutoWidth()[SNew(SComboBox<TSharedPtr<FString>>).OptionsSource(&Brushes).InitiallySelectedItem(Brushes[0])
                    .OnGenerateWidget_Lambda([](TSharedPtr<FString> Value){return SNew(STextBlock).Text(FText::FromString(*Value));})
                    .OnSelectionChanged_Lambda([this](TSharedPtr<FString> Value,ESelectInfo::Type){Brush=static_cast<EBrush>(Brushes.IndexOfByKey(Value));LinkCell=FIntPoint(-1,-1);if(Brush==EBrush::Bridge)Id=TEXT("br1");if(Brush==EBrush::Switch)Id=TEXT("sw1");})
                    [SNew(STextBlock).Text_Lambda([this](){return FText::FromString(*Brushes[int32(Brush)]);})]]
                +SHorizontalBox::Slot().AutoWidth().Padding(8,0)[SNew(STextBlock).Text(FText::FromString("Brush ID:"))]
                +SHorizontalBox::Slot().FillWidth(1)[SNew(SEditableTextBox).Text_Lambda([this](){return FText::FromString(Id);}).OnTextChanged_Lambda([this](const FText& Text){Id=Text.ToString();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SButton).Text(FText::FromString("Auto ID")).OnClicked_Lambda([this](){
                    const FString Prefix=Brush==EBrush::Bridge?TEXT("br"):TEXT("sw");int32 Index=1;
                    if(Selected.IsValid())while(Selected->Data.Tiles.ContainsByPredicate([&](const auto& T){return T.Id==FName(*(Prefix+FString::FromInt(Index)));}))++Index;
                    Id=Prefix+FString::FromInt(Index);return FReply::Handled();})]
                +SHorizontalBox::Slot().AutoWidth()[SNew(SCheckBox).IsChecked_Lambda([this](){return bHeavy?ECheckBoxState::Checked:ECheckBoxState::Unchecked;}).OnCheckStateChanged_Lambda([this](ECheckBoxState State){bHeavy=State==ECheckBoxState::Checked;})[SNew(STextBlock).Text(FText::FromString("Heavy switch (upright / once)"))]]
            ]
            +SVerticalBox::Slot().FillHeight(1)[SNew(SSplitter)
                +SSplitter::Slot().Value(.35f)[Details.ToSharedRef()]
                +SSplitter::Slot().Value(.65f)[SNew(SScrollBox).Orientation(Orient_Horizontal)+SScrollBox::Slot()[SNew(SScrollBox)+SScrollBox::Slot()[Grid.ToSharedRef()]]]
            ]
            +SVerticalBox::Slot().AutoHeight().Padding(6)[SNew(STextBlock).AutoWrapText(true).Text_Lambda([this](){return FText::FromString(Status);})]
        ];
    }
    void Paint(FIntPoint Cell)
    {
        if(!Selected.IsValid())return;auto& D=Selected->Data;
        if(Brush==EBrush::Link)
        {
            if(LinkCell.X<0){LinkCell=Cell;Status=TEXT("Select a bridge after a switch, or a switch after a bridge.");return;}
            auto* A=D.Tiles.FindByPredicate([this](const auto& T){return T.Position==LinkCell;});
            auto* B=D.Tiles.FindByPredicate([Cell](const auto& T){return T.Position==Cell;});
            if(A&&B)
            {
                if(A->Type==EBloxorzTileType::Bridge)Swap(A,B);
                if(A->Type==EBloxorzTileType::Switch&&B->Type==EBloxorzTileType::Bridge&&!B->Id.IsNone())
                {
                    if(A->Targets.Contains(B->Id)){A->Targets.Remove(B->Id);Status=TEXT("Bridge group unlinked.");}
                    else{A->Targets.Add(B->Id);Status=TEXT("Bridge group linked: ")+A->Id.ToString()+TEXT(" -> ")+B->Id.ToString();}
                }
                else Status=TEXT("Choose one Switch and one Bridge with an ID.");
            }
            LinkCell=FIntPoint(-1,-1);
        }
        else if(Brush==EBrush::Start){D.Start.Anchor=Cell;Status=TEXT("Start placed. Ensure all starting occupied cells have support.");}
        else if(Brush==EBrush::Empty)D.Tiles.RemoveAll([Cell](const auto& T){return T.Position==Cell;});
        else
        {
            EBloxorzTileType Type=Brush==EBrush::Goal?EBloxorzTileType::Goal:Brush==EBrush::Fragile?EBloxorzTileType::Fragile:Brush==EBrush::Switch?EBloxorzTileType::Switch:Brush==EBrush::Bridge?EBloxorzTileType::Bridge:EBloxorzTileType::Normal;
            if(Type==EBloxorzTileType::Goal){for(auto& T:D.Tiles)if(T.Type==EBloxorzTileType::Goal)T.Type=EBloxorzTileType::Normal;D.Goal=Cell;}
            auto* Existing=D.Tiles.FindByPredicate([Cell](const auto& T){return T.Position==Cell;});
            FBloxorzTile New;New.Position=Cell;New.Type=Type;
            if(Type==EBloxorzTileType::Switch||Type==EBloxorzTileType::Bridge)New.Id=FName(*Id.TrimStartAndEnd());
            New.SwitchBehavior=bHeavy?EBloxorzSwitchBehavior::HeavyOneShot:EBloxorzSwitchBehavior::Toggle;
            if(Existing&&Existing->Type==Type&&Type==EBloxorzTileType::Switch)New.Targets=Existing->Targets;
            if(Existing)*Existing=New;else D.Tiles.Add(New);
        }
        Selected->MarkPackageDirty();
    }
    FReply Create()
    {
        auto& Tools=FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();FString Package,Name;
        Tools.CreateUniqueAssetName(TEXT("/Game/Levels/NewLevel"),TEXT(""),Package,Name);
        auto* Factory=NewObject<UDataAssetFactory>();Factory->DataAssetClass=UBloxorzLevelAsset::StaticClass();
        auto* Asset=Cast<UBloxorzLevelAsset>(Tools.CreateAsset(Name,FPackageName::GetLongPackagePath(Package),UBloxorzLevelAsset::StaticClass(),Factory));
        if(Asset){Asset->Data.LevelId=FName(*Name);Asset->MarkPackageDirty();Selected.Reset(Asset);Details->SetObject(Asset);Grid->Invalidate(EInvalidateWidgetReason::Layout);Status=TEXT("New empty puzzle. Set dimensions in Details, paint support, then place Start and Goal.");}
        return FReply::Handled();
    }
    FReply Save()
    {
        TArray<UPackage*> Packages;if(Selected.IsValid())Packages.Add(Selected->GetOutermost());if(Campaign.IsValid())Packages.AddUnique(Campaign->GetOutermost());
        const auto Result=FEditorFileUtils::PromptForCheckoutAndSave(Packages,true,false);
        Status=Result==FEditorFileUtils::PR_Success?TEXT("Puzzle and campaign saved."):TEXT("Save was cancelled or failed; changes remain dirty.");return FReply::Handled();
    }
    FReply Validate()
    {
        if(!Selected.IsValid())return FReply::Handled();const auto R=FBloxorzLevelValidator::Validate(Selected->Data);
        if(!R.Errors.IsEmpty())Status=FString::Join(R.Errors,TEXT("\n"));
        else if(R.bSolved)Status=FString::Printf(TEXT("SOLVABLE: %d moves; %d states. Path: %s"),R.Solution.Len(),R.Explored,*R.Solution);
        else Status=R.bLimitReached?TEXT("Search limit reached: solvability unknown. Simplify puzzle/switch state or increase the validator budget in code."):TEXT("NOT SOLVABLE under the current rules.");
        if(!R.Warnings.IsEmpty())Status+=TEXT("\nWarnings: ")+FString::Join(R.Warnings,TEXT(" "));
        return FReply::Handled();
    }
    FReply AddToCampaign()
    {
        if(!Selected.IsValid()||!Campaign.IsValid()){Status=TEXT("Select a level and ensure /Game/Levels/DA_Campaign exists.");return FReply::Handled();}
        FScopedTransaction Transaction(FText::FromString(TEXT("Add Bloxorz level to campaign")));Campaign->Modify();Campaign->Levels.AddUnique(TSoftObjectPtr<UBloxorzLevelAsset>(Selected.Get()));Campaign->MarkPackageDirty();Status=TEXT("Added to campaign. Use Campaign order to reorder Levels, then Save.");return FReply::Handled();
    }
    FReply Play()
    {
        if(!Selected.IsValid())return FReply::Handled();Validate();const auto R=FBloxorzLevelValidator::Validate(Selected->Data);if(!R.bSolved)return FReply::Handled();
        TArray<UPackage*> Packages{Selected->GetOutermost()};if(FEditorFileUtils::PromptForCheckoutAndSave(Packages,true,false)!=FEditorFileUtils::PR_Success)return FReply::Handled();
        FRequestPlaySessionParams Params;Params.SessionDestination=EPlaySessionDestinationType::NewProcess;Params.GlobalMapOverride=TEXT("/Game/Maps/Puzzle");Params.AdditionalStandaloneCommandLineParameters=TEXT("-BloxorzLevelAsset=")+Selected->GetPathName();
        GEditor->RequestPlaySession(Params);Status=TEXT("Launching selected puzzle standalone; campaign progress will not be changed.");return FReply::Handled();
    }
};

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPaintAndLinkTest,"Bloxorz.Authoring.PaintAndLink",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FPaintAndLinkTest::RunTest(const FString&)
{
    auto Designer=SNew(SDesigner);
    Designer->Selected.Reset(NewObject<UBloxorzLevelAsset>(GetTransientPackage(),NAME_None,RF_Transactional));
    Designer->Selected->Data.GridSize={8,8};
    Designer->Brush=EBrush::Normal;Designer->Paint({1,1});Designer->Paint({2,1});
    TestEqual(TEXT("Paint adds cells"),Designer->Selected->Data.Tiles.Num(),2);
    Designer->Brush=EBrush::Start;Designer->Paint({1,1});TestTrue(TEXT("Start marker"),Designer->Selected->Data.Start.Anchor==FIntPoint(1,1));
    Designer->Brush=EBrush::Goal;Designer->Paint({2,1});Designer->Paint({3,1});
    TestEqual(TEXT("Moving goal keeps exactly one goal tile"),Designer->Selected->Data.Tiles.FilterByPredicate([](const auto& T){return T.Type==EBloxorzTileType::Goal;}).Num(),1);
    Designer->Brush=EBrush::Switch;Designer->Id=TEXT("sw1");Designer->Paint({4,1});
    Designer->Brush=EBrush::Bridge;Designer->Id=TEXT("br1");Designer->Paint({5,1});Designer->Paint({6,1});
    Designer->Brush=EBrush::Link;Designer->Paint({5,1});Designer->Paint({4,1});
    auto* Switch=Designer->Selected->Data.Tiles.FindByPredicate([](const auto& T){return T.Type==EBloxorzTileType::Switch;});
    TestTrue(TEXT("Reverse-order linking targets bridge group"),Switch&&Switch->Targets.Contains(TEXT("br1")));
    Designer->Brush=EBrush::Switch;Designer->Id=TEXT("sw1");Designer->bHeavy=true;Designer->Paint({4,1});
    Switch=Designer->Selected->Data.Tiles.FindByPredicate([](const auto& T){return T.Type==EBloxorzTileType::Switch;});
    TestTrue(TEXT("Switch repaint preserves targets"),Switch&&Switch->Targets.Contains(TEXT("br1")));
    Designer->Brush=EBrush::Link;Designer->Paint({4,1});Designer->Paint({6,1});
    TestTrue(TEXT("Second link toggles target off"),Switch->Targets.IsEmpty());
    Designer->Brush=EBrush::Empty;Designer->Paint({1,1});TestTrue(TEXT("Erase removes support"),!FBloxorzSimulation::FindTile(Designer->Selected->Data,{1,1}));
    return true;
}
#endif
}

class FBloxorzUnrealToolsModule : public IModuleInterface
{
public:
    TUniquePtr<FAutoConsoleCommand> OpenCommand;
    void StartupModule() override
    {
        FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BloxorzDesigner::TabId,FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){return SNew(SDockTab).TabRole(ETabRole::NomadTab)[SNew(BloxorzDesigner::SDesigner)];})).SetDisplayName(FText::FromString(TEXT("Bloxorz Level Designer")));
        UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this,&FBloxorzUnrealToolsModule::RegisterMenus));
        OpenCommand=MakeUnique<FAutoConsoleCommand>(TEXT("Bloxorz.LevelDesigner"),TEXT("Open the puzzle authoring tool"),FConsoleCommandDelegate::CreateLambda([](){FGlobalTabmanager::Get()->TryInvokeTab(BloxorzDesigner::TabId);}));
    }
    void RegisterMenus()
    {
        FToolMenuOwnerScoped Owner(this);auto* Menu=UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
        Menu->FindOrAddSection("Bloxorz").AddMenuEntry("BloxorzDesigner",FText::FromString("Bloxorz Level Designer"),FText::FromString("Paint, link, validate and play asset-based puzzles."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([](){FGlobalTabmanager::Get()->TryInvokeTab(BloxorzDesigner::TabId);} )));
    }
    void ShutdownModule() override
    {
        OpenCommand.Reset();
        UToolMenus::UnRegisterStartupCallback(this);UToolMenus::UnregisterOwner(this);FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BloxorzDesigner::TabId);
    }
};
IMPLEMENT_MODULE(FBloxorzUnrealToolsModule,BloxorzUnrealTools)
