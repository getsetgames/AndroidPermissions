//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#include "AndroidPermissions.h"
#include "AndroidPermissionsPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogAndroidPermissions);

#define LOCTEXT_NAMESPACE "FAndroidPermissionsModule"

void FAndroidPermissionsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAndroidPermissionsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAndroidPermissionsModule, AndroidPermissions)
