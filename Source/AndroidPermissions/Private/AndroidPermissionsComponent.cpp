//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#include "AndroidPermissionsComponent.h"
#include "AndroidPermissionsPrivatePCH.h"

void UAndroidPermissionsComponent::OnRegister()
{
	Super::OnRegister();
		
	UAndroidPermissionsComponent::RequestPermissionsResultDelegate.AddUObject(this, &UAndroidPermissionsComponent::RequestPermissionsResult_Handler);
}

void UAndroidPermissionsComponent::OnUnregister()
{
	Super::OnUnregister();
	
	UAndroidPermissionsComponent::RequestPermissionsResultDelegate.RemoveAll(this);	
}

UAndroidPermissionsComponent::FRequestPermissionsResultDelegate UAndroidPermissionsComponent::RequestPermissionsResultDelegate;