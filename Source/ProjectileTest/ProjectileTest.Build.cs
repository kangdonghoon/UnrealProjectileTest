// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectileTest : ModuleRules
{
	public ProjectileTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
