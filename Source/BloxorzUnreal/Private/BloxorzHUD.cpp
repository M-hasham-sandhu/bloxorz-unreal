#include "BloxorzGameMode.h"
#include "BloxorzBoard.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "CanvasItem.h"
#include "Engine/Font.h"

static ABloxorzBoard* FindPuzzle(UWorld* World){for(TActorIterator<ABloxorzBoard> It(World);It;++It)return *It;return nullptr;}

void ABloxorzHUD::DrawHUD()
{
    Super::DrawHUD();auto* B=FindPuzzle(GetWorld());if(!B||!Canvas||Canvas->SizeX<1||Canvas->SizeY<1)return;
    Buttons.Reset();
    const float Scale=FMath::Min(Canvas->SizeX/1440.f,Canvas->SizeY/900.f);
    const float W=Canvas->SizeX/Scale,H=Canvas->SizeY/Scale;
    const FLinearColor Ink(.91f,.96f,.97f),Muted(.50f,.64f,.68f),Teal(.26f,.86f,.83f);
    if(!DisplayFont)DisplayFont=LoadObject<UFont>(nullptr,TEXT("/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField"));
    auto Rect=[&](FLinearColor C,float X,float Y,float Width,float Height){DrawRect(C,X*Scale,Y*Scale,Width*Scale,Height*Scale);};
    auto Text=[&](const FString& S,float X,float Y,float Size,FLinearColor C)
    {
        const UFont* Font=DisplayFont?DisplayFont.Get():GEngine->GetMediumFont();
        FCanvasTextItem Item(FVector2D(FMath::RoundToFloat(X*Scale),FMath::RoundToFloat(Y*Scale)),FText::FromString(S),Font,C);
        Item.Scale=FVector2D(19*Size*Scale/FMath::Max(1,Font->GetMaxCharHeight()));
        Canvas->DrawItem(Item);
    };
    // Rounded shapes are native canvas strips: no image assets or fixed-resolution UI textures.
    auto Round=[&](FLinearColor C,float X,float Y,float Width,float Height,float Radius)
    {
        Radius=FMath::Min(Radius,FMath::Min(Width,Height)*.5f);
        Rect(C,X,Y+Radius,Width,Height-2*Radius);
        const float Slice=Radius/16;
        for(int32 I=0;I<16;++I)
        {
            const float D=Radius-(I+.5f)*Slice;
            const float Inset=Radius-FMath::Sqrt(FMath::Max(0.f,Radius*Radius-D*D));
            Rect(C,X+Inset,Y+I*Slice,Width-2*Inset,Slice+.02f);
            Rect(C,X+Inset,Y+Height-(I+1)*Slice,Width-2*Inset,Slice+.02f);
        }
    };
    auto Line=[&](float X1,float Y1,float X2,float Y2,FLinearColor C,float Thickness){DrawLine(X1*Scale,Y1*Scale,X2*Scale,Y2*Scale,C,Thickness*Scale);};
    float Opacity=1;
    auto Alpha=[&](FLinearColor C){C.A*=Opacity;return C;};
    float MX=0,MY=0;GetOwningPlayerController()->GetMousePosition(MX,MY);
    auto Button=[&](const FString& Label,const FString& Key,float X,float Y,float Width,FName Action,bool Primary,FLinearColor Accent,float Height=52.f)
    {
        const FBox2D Box(FVector2D(X*Scale,Y*Scale),FVector2D((X+Width)*Scale,(Y+Height)*Scale));
        const bool Hover=Box.IsInside(FVector2D(MX,MY));
        Round(Alpha(Primary?(Hover?Accent*1.12f:Accent):FLinearColor(.065f,.115f,.14f)),X,Y,Width,Height,10);
        Text(Label,X+18,Y+(Height-20)*.5f,1.02f,Alpha(Primary?FLinearColor(.02f,.085f,.09f):Ink));
        if(!Key.IsEmpty())Text(Key,X+Width-54,Y+(Height-17)*.5f,.77f,Alpha(Primary?FLinearColor(.05f,.22f,.22f):Muted));
        Buttons.Add({Box,Action});
    };

    // Gameplay is intentionally free of branding and bottom-corner instruction text.
    Button(TEXT("MENU"),TEXT(""),32,28,88,TEXT("Menu"),false,Teal,36);
    Button(B->IsMuted()?TEXT("AUDIO OFF"):TEXT("AUDIO ON"),TEXT(""),130,28,124,TEXT("Mute"),false,Teal,36);
    Round(FLinearColor(.025f,.05f,.067f,.75f),W-256,24,224,83,12);
    Text(FString::Printf(TEXT("LEVEL  %02d / %02d"),B->GetLevelIndex()+1,B->GetLevelCount()),W-236,38,1.04f,Ink);
    Text(FString::Printf(TEXT("MOVES %02d     BEST %s"),B->GetMoveCount(),B->GetBest()?*FString::FromInt(B->GetBest()):TEXT("--")),W-236,71,.84f,Muted);

    const bool Menu=B->IsMenuOpen(),Won=B->HasWon(),Failed=B->IsDead();
    if(!Menu&&!Won&&!Failed){LastPanel=NAME_None;PanelAge=0;return;}
    Buttons.Reset();
    const FName Kind=Menu?TEXT("Menu"):Won?TEXT("Win"):TEXT("Fail");
    if(Kind!=LastPanel){LastPanel=Kind;PanelAge=0;}
    PanelAge+=GetWorld()->GetDeltaSeconds();Opacity=FMath::Clamp(PanelAge/.24f,0.f,1.f);Opacity=Opacity*Opacity*(3-2*Opacity);
    const FLinearColor Accent=Menu?Teal:Won?FLinearColor(.32f,.9f,.66f):FLinearColor(.98f,.59f,.35f);
    Rect(Alpha(FLinearColor(.005f,.012f,.02f,.63f)),0,0,W,H);
    const float PW=580,PH=Menu?456.f:410.f;
    const float X=(W-PW)*.5f,Y=(H-PH)*.5f+(1-Opacity)*18;
    Round(Alpha(FLinearColor(0,0,0,.22f)),X-7,Y+9,PW+14,PH+8,25);
    Round(Alpha(FLinearColor(.12f,.21f,.24f)),X,Y,PW,PH,20);
    Round(Alpha(FLinearColor(.021f,.042f,.058f)),X+1,Y+1,PW-2,PH-2,19);
    Round(Alpha(Accent),X+32,Y+30,4,48,2);
    Text(Menu?TEXT("TAKE A BREATH"):Won?TEXT("PUZZLE SOLVED"):TEXT("TRY ANOTHER ROUTE"),X+52,Y+29,.79f,Alpha(Accent));
    Text(Menu?TEXT("Paused"):Won?TEXT("Level complete"):TEXT("Level failed"),X+50,Y+50,2.25f,Alpha(Ink));
    Text(Menu?TEXT("Your puzzle will be right where you left it."):Won?TEXT("Nicely done. On to the next challenge."):
        B->GetRevives()>0?TEXT("Return to your last safe position, or start fresh."):TEXT("No revives left. A fresh start is a fresh perspective."),X+32,Y+108,.95f,Alpha(Muted));

    if(Menu)
    {
        Round(Alpha(FLinearColor(.04f,.073f,.09f)),X+32,Y+144,516,124,12);
        Text(TEXT("CONTROLS"),X+50,Y+160,.78f,Alpha(Muted));
        Text(TEXT("WASD / arrows   Move       R   Restart"),X+50,Y+191,.98f,Alpha(Ink));
        Text(TEXT("PgUp / PgDn   Levels       M   Audio"),X+50,Y+225,.98f,Alpha(Ink));
        Button(TEXT("Resume puzzle"),TEXT("ENTER"),X+32,Y+289,516,TEXT("Resume"),true,Accent);
        Button(TEXT("Restart level"),TEXT("R"),X+32,Y+353,252,TEXT("Restart"),false,Accent);
        Button(B->IsMuted()?TEXT("Enable audio"):TEXT("Mute audio"),TEXT("M"),X+296,Y+353,252,TEXT("Mute"),false,Accent);
        return;
    }

    auto Stat=[&](const FString& Label,const FString& Value,float SX,float Width)
    {
        Round(Alpha(FLinearColor(.042f,.075f,.094f)),SX,Y+150,Width,86,12);
        Text(Label,SX+18,Y+165,.77f,Alpha(Muted));Text(Value,SX+18,Y+187,1.7f,Alpha(Ink));
    };
    if(Won)
    {
        Stat(TEXT("LEVEL"),FString::Printf(TEXT("%02d"),B->GetLevelIndex()+1),X+32,164);
        Stat(TEXT("MOVES"),FString::FromInt(B->GetMoveCount()),X+208,164);
        Stat(TEXT("BEST"),B->GetBest()?FString::FromInt(B->GetBest()):TEXT("--"),X+384,164);
        Button(B->GetLevelCount()==1?TEXT("Play again"):TEXT("Next level"),TEXT("ENTER"),X+32,Y+258,516,TEXT("Next"),true,Accent);
        Button(TEXT("Replay level"),TEXT("R"),X+32,Y+322,252,TEXT("Restart"),false,Accent);
        Button(TEXT("Menu"),TEXT("ESC"),X+296,Y+322,252,TEXT("Menu"),false,Accent);
    }
    else
    {
        Stat(TEXT("REVIVES REMAINING"),FString::FromInt(B->GetRevives()),X+32,252);
        Stat(TEXT("MOVES TAKEN"),FString::FromInt(B->GetMoveCount()),X+296,252);
        const bool CanRevive=B->GetRevives()>0;
        Button(CanRevive?TEXT("Revive at safe position"):TEXT("Restart level"),CanRevive?TEXT("ENTER"):TEXT("R"),X+32,Y+258,516,CanRevive?TEXT("Revive"):TEXT("Restart"),true,Accent);
        Button(CanRevive?TEXT("Restart level"):TEXT("Menu"),CanRevive?TEXT("R"):TEXT("ESC"),X+32,Y+322,516,CanRevive?TEXT("Restart"):TEXT("Menu"),false,Accent);
    }
}

void ABloxorzHUD::HandleClick()
{
    auto* B=FindPuzzle(GetWorld());if(!B)return;float X=0,Y=0;GetOwningPlayerController()->GetMousePosition(X,Y);
    for(int32 I=Buttons.Num()-1;I>=0;--I)if(Buttons[I].Box.IsInside(FVector2D(X,Y)))
    {
        const FName Action=Buttons[I].Action;
        if(Action==TEXT("Mute"))B->ToggleMute();else if(Action==TEXT("Resume")||Action==TEXT("Menu"))B->ToggleMenu();
        else if(Action==TEXT("Restart"))B->Restart();else if(Action==TEXT("Next"))B->NextLevel();else if(Action==TEXT("Revive"))B->Revive();
        break;
    }
}
