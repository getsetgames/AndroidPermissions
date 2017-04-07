//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ModuleManager.h"

class FAndroidPermissionsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};