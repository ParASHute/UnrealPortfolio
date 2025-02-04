// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Portfolio : ModuleRules
{
	public Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime", 
			"AIModule"	// AI모듈 추가
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput", 
			// GAS추가
			"GameplayAbilities", "GameplayTags", "GameplayTasks", 
			// WidgetComponent추가
			"UMG"
		});
	}
}
