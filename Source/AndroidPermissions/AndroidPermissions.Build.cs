//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

using UnrealBuildTool;
using System.IO;

public class AndroidPermissions : ModuleRules
{
	public AndroidPermissions(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"AndroidPermissions/Public",
				"../../../../Source/Runtime/Core/Public",
				"../../../../Source/Runtime/Launch/Public"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"AndroidPermissions/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
			
		PublicIncludePathModuleNames.Add("Launch");
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "AndroidPermissions_APL.xml")));
		}

	}
}
