// Copyright (c) XiaoGang.2023.All Rights Reserved.

#include "XGLoginClientBPLibrary.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "XGLoginClientAdapter.h"

UXGLoginClientBPLibrary::UXGLoginClientBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}



FString UXGLoginClientBPLibrary::XGGetOperatingSystemId()
{
	FString OperatingSystemId = TEXT("");
	OperatingSystemId = FPlatformMisc::GetOperatingSystemId();
	OperatingSystemId.ReplaceInline(TEXT("-"), TEXT(""));

#if PLATFORM_ANDROID

	OperatingSystemId = FXGLoginClientAdapter::GetID();

#endif // PLATFORM_ANDROID


	return OperatingSystemId;
}

FString UXGLoginClientBPLibrary::XGAndridoTest()
{
	return FXGLoginClientAdapter::GetID();
}




