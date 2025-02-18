// Copyright (c) XiaoGang.2023.All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "XGLoginClientBPLibrary.generated.h"


UCLASS()
class XGLOGINCLIENT_API UXGLoginClientBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UXGLoginClientBPLibrary(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetLocalMachineID",
		Keywords = "XGLoginClient Execute OperatingSystemId"), Category = "XGLoginClient|Machine")
	static FString XGGetOperatingSystemId();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XGAndridoTest",
		Keywords = "XGLoginClient Andriod Test"), Category = "XGLoginClient|Machine")
	static FString XGAndridoTest();


};

