using UnrealBuildTool;
public class BloxorzUnrealTools : ModuleRules
{
    public BloxorzUnrealTools(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage=PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[]{"Core","CoreUObject","Engine","BloxorzUnreal","UnrealEd","Slate","SlateCore","ToolMenus","AssetTools","PropertyEditor","InputCore"});
    }
}
