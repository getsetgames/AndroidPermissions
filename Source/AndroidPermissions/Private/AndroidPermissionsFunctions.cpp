//
//  Created by Derek van Vliet on 2017-04-07.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#include "AndroidPermissionsFunctions.h"
#include "AndroidPermissionsPrivatePCH.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

#if PLATFORM_ANDROID
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeRequestPermissionsResult(JNIEnv* jenv,
                                                                                      jobject thiz,
                                                                                      jint requestCode
                                                                                      jobjectArray permissions,
                                                                                      jintArray grantResults)
{
    UE_LOG(LogAndroidPermissions, Log, TEXT("Java_com_epicgames_ue4_GameActivity_nativeRequestPermissionsResult"));
    
    int32 RequestCode = requestCode;
    TArray<FString> Permissions;
    TArray<int32> GrantResults;
    
    jsize jNumPermissions = jenv->GetArrayLength(permissions);
    jsize jNumGrantResults = jenv->GetArrayLength(grantResults);
    jint* jGrantResults = jenv->GetIntArrayElements(grantResults, NULL);

    for (int i = 0; i < jNumPermissions; i++)
    {
        jstring jPermission = (jstring)jenv->GetObjectArrayElement(permissions, i);
        const char* charsPermission = jenv->GetStringUTFChars(jProductID, 0);

        FString ProductID(FString(UTF8_TO_TCHAR(charsPermission)));

        jenv->ReleaseStringUTFChars(jPermission, charsPermission);
        jenv->DeleteLocalRef(jPermission);

        Permissions.Add(Permission);
    }

    for (int i = 0; i < jNumGrantResults; i++)
    {
        int32 GrantResult = jGrantResults[i];
        GrantResults.Add(GrantResult);
    }
    
    UAndroidPermissionsComponent::RequestPermissionsResultDelegate.Broadcast(RequestCode,Permissions,GrantResults);
}
#endif





