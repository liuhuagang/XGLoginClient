// Copyright (c) XiaoGang.2025.All Rights Reserved.

#include "XGLoginClientAdapter.h"

#if PLATFORM_ANDROID

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidJava.h"

#endif


#if PLATFORM_ANDROID

FString GameActivity_GetName(JNIEnv* Env)
{
	//方法签名
	jmethodID InitMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "GetName", "()Ljava/lang/String;", false);
	jobject javaMsg = FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, InitMethodID);
	FString message = FJavaHelper::FStringFromLocalRef(Env, (jstring)javaMsg);
	return message;
}

FString GetDeviceID()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jmethodID InitMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getDeviceId", 
	"(Landroid/content/Context;)Ljava/lang/String;", false);

	jobject Context = FAndroidApplication::GetGameActivityThis();
	jobject javaMsg = FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, InitMethodID, Context);

	FString message = FJavaHelper::FStringFromLocalRef(Env, (jstring)javaMsg);

	return message;
}

#endif



FXGLoginClientAdapter* FXGLoginClientAdapter::Instance =nullptr;

FXGLoginClientAdapter* FXGLoginClientAdapter::Get()
{
	if (Instance==nullptr)
	{
		Instance = new FXGLoginClientAdapter();
	}
	return Instance;
}

FXGLoginClientAdapter::FXGLoginClientAdapter()
{
}

FXGLoginClientAdapter::~FXGLoginClientAdapter()
{
}

FString FXGLoginClientAdapter::GetName()
{
	FString msg=TEXT("123456");
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (nullptr != Env)
	{
		msg = GameActivity_GetName(Env);
	}
#endif
	return msg;
}

FString FXGLoginClientAdapter::GetID()
{
	FString msg = TEXT("123456");

#if PLATFORM_ANDROID
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		if (nullptr != Env)
		{
			msg = GetDeviceID();
		}
#endif


	return msg;
}
