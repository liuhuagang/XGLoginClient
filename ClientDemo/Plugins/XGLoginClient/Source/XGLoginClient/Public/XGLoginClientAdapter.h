// Copyright (c) XiaoGang.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidJava.h"

#endif


class XGLOGINCLIENT_API FXGLoginClientAdapter
{
public:

	static FXGLoginClientAdapter* Get();

public:

	FXGLoginClientAdapter();

	~FXGLoginClientAdapter();

public:
	
	static FString GetName();

	static FString GetID();

private:

	static FXGLoginClientAdapter* Instance;

};
