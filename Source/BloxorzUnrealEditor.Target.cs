using UnrealBuildTool;
public class BloxorzUnrealEditorTarget : TargetRules
{
    public BloxorzUnrealEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("BloxorzUnreal");
    }
}
