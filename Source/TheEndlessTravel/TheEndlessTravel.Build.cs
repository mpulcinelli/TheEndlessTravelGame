// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheEndlessTravel : ModuleRules
{
	public TheEndlessTravel(ReadOnlyTargetRules Target) : base(Target)
	{
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
        bEnforceIWYU = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "PhysX", "APEX", "ApexDestruction" });
    }
}
