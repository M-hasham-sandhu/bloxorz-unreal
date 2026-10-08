using UnrealBuildTool;
public class BloxorzUnrealTarget : TargetRules
{
    public BloxorzUnrealTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("BloxorzUnreal");
    }
}
