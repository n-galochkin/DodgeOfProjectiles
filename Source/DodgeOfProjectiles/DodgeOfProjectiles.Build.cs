// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DodgeOfProjectiles : ModuleRules
{
	public DodgeOfProjectiles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "AIModule" });
	}
}
