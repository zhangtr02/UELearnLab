// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UELearnLab : ModuleRules
{
	public UELearnLab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UELearnLab",
			"UELearnLab/Variant_Platforming",
			"UELearnLab/Variant_Platforming/Animation",
			"UELearnLab/Variant_Combat",
			"UELearnLab/Variant_Combat/AI",
			"UELearnLab/Variant_Combat/Animation",
			"UELearnLab/Variant_Combat/Gameplay",
			"UELearnLab/Variant_Combat/Interfaces",
			"UELearnLab/Variant_Combat/UI",
			"UELearnLab/Variant_SideScrolling",
			"UELearnLab/Variant_SideScrolling/AI",
			"UELearnLab/Variant_SideScrolling/Gameplay",
			"UELearnLab/Variant_SideScrolling/Interfaces",
			"UELearnLab/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
