namespace UnrealBuildTool.Rules
{
  public class FirstPlugin : ModuleRules
  {
     public FirstPlugin(ReadOnlyTargetRules Target) : base(Target)
     {
        PublicDependencyModuleNames.AddRange(
           new string[] //Зависимости нашего модуля
           {
              "Core",
              "CoreUObject",
              "Engine",
			  "DeveloperSettings",
			  "Projects",
		   }
        );
	 }
  }
}