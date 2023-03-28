// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RunnerSurvival : ModuleRules
{
	public RunnerSurvival(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"FirstPlugin",
			"MultiplayerSessions",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"GameplayAbilities",
			"GameplayTags",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "FirstPlugin",	"MultiplayerSessions" });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"RunnerSurvival/Public/Player",
			"RunnerSurvival/Public/Components",
			"RunnerSurvival/Public/UI",
			"RunnerSurvival/Public/Actors",
			"RunnerSurvival/Public/GameModes",
			"RunnerSurvival/Public/Managers",
			"RunnerSurvival/Public/Radiation"

		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
