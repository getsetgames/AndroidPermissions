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
void CreateJavaArray(JNIEnv *Env, jobjectArray &jValuesArray, TArray<FString> values)
{
	for (uint32 Param = 0; Param < values.Num(); Param++)
	{
		jstring StringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*values[Param]));
		
		Env->SetObjectArrayElement(jValuesArray, Param, StringValue);
		Env->DeleteLocalRef(StringValue);
	}
}
#endif

bool UAndroidPermissionsFunctions::HasPermission(FString Permission)
{
    #if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env,
														   FJavaWrapper::GameActivityClassID,
														   "AndroidThunkJava_HasPermission",
														   "(Ljava/lang/String;)Z",
														   false);
		
		jstring jPermission = Env->NewStringUTF(TCHAR_TO_UTF8(*Permission));
		bool Result = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method, jPermission);
		Env->DeleteLocalRef(jPermission);
		
		return Result;
	}
    #endif

    return false;
}

bool UAndroidPermissionsFunctions::HasPermissions(TArray<FString> Permissions)
{
	for (int i = 0; i < Permissions.Num(); i++)
	{
		if (UAndroidPermissionsFunctions::HasPermission(Permissions[i]) == false)
		{
			return false;
		}
	}

    return true;
}

void UAndroidPermissionsFunctions::RequestPermissions(TArray<FString> Permissions, int32 RequestCode)
{
    #if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env,
														   FJavaWrapper::GameActivityClassID,
														   "AndroidThunkJava_RequestPermissions",
														   "([Ljava/lang/String;I)V",
														   false);
		
		jobjectArray jPermissions = (jobjectArray)Env->NewObjectArray(Permissions.Num(), FJavaWrapper::JavaStringClass, NULL);
		CreateJavaArray(Env, jPermissions, Permissions);
		
		jint jRequestCode = (jint)RequestCode;
		
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jPermissions, jRequestCode);
		Env->DeleteLocalRef(jPermissions);		
	}
    #endif
}

#if PLATFORM_ANDROID
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeRequestPermissionsResult(JNIEnv* jenv,
                                                                                      jobject thiz,
                                                                                      jint requestCode,
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
        const char* charsPermission = jenv->GetStringUTFChars(jPermission, 0);

        FString Permission(FString(UTF8_TO_TCHAR(charsPermission)));

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





