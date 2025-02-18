// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "XGLoginServerHttpType.h"

#include "XGLoginServerLoginMRespType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGGetMachineAndRegisterTimeRespData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString MachineID = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FDateTime MachineRegisterTime = FDateTime();
};
