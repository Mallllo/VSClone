// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VSClone : ModuleRules
{
	public VSClone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","GameplayTasks", "UMG", "OnlineSubsystem" });
    }
}
