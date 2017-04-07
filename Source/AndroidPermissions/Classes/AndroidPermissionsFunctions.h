//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "AndroidPermissionsFunctions.generated.h"

UCLASS(NotBlueprintable)
class UAndroidPermissionsFunctions : public UObject {
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintPure, meta = (Keywords = "android permissions"), Category = "Android")
    static bool HasPermission(FString Permission);

    UFUNCTION(BlueprintPure, meta = (Keywords = "android permissions"), Category = "Android")
    static bool HasPermissions(TArray<FString> Permissions);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "android permissions"), Category = "Android")
    static void RequestPermissions(TArray<FString> Permissions, int32 RequestCode);
};
