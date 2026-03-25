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
			"GameplayTags",
			"MassEntity",
			"MassCommon",
			"MassMovement",
			"MassSpawner",
			"NavigationSystem",
			"SmartObjectsModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UELearnLab",
			"UELearnLab/Variant/Variant_Platforming",
			"UELearnLab/Variant/Variant_Platforming/Animation",
			"UELearnLab/Variant/Variant_Combat",
			"UELearnLab/Variant/Variant_Combat/AI",
			"UELearnLab/Variant/Variant_Combat/Animation",
			"UELearnLab/Variant/Variant_Combat/Gameplay",
			"UELearnLab/Variant/Variant_Combat/Interfaces",
			"UELearnLab/Variant/Variant_Combat/UI",
			"UELearnLab/Variant/Variant_SideScrolling",
			"UELearnLab/Variant/Variant_SideScrolling/AI",
			"UELearnLab/Variant/Variant_SideScrolling/Gameplay",
			"UELearnLab/Variant/Variant_SideScrolling/Interfaces",
			"UELearnLab/Variant/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
