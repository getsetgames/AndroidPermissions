//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "Components/ActorComponent.h"
#include "AndroidPermissionsFunctions.h"
#include "AndroidPermissionsComponent.generated.h"

UCLASS(ClassGroup=Advertising, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UAndroidPermissionsComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	void OnRegister() override;
	void OnUnregister() override;

   	DECLARE_MULTICAST_DELEGATE_ThreeParams(FRequestPermissionsResultDelegate, int32, const TArray<FString>&, const TArray<int32>&);
    
    static FRequestPermissionsResultDelegate RequestPermissionsResultDelegate;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRequestPermissionsResultDynDelegate, int32, RequestCode, const TArray<FString>&, Permissions, const TArray<int32>&, GrantResults);

    UPROPERTY(BlueprintAssignable)
	FRequestPermissionsResultDynDelegate RequestPermissionsResult;

private:	
	void RequestPermissionsResult_Handler(int32 RequestCode, const TArray<FString>& Permissions, const TArray<int32>& GrantResults) { RequestPermissionsResult.Broadcast(RequestCode, Permissions, GrantResults); }
};
