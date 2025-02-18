// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MySqlDemo : ModuleRules
{
	public MySqlDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"XGLoginClient",
        });
	}
}
