// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "XGLoginServerLoginRespType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGRegisterRespData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserName= TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserID= TEXT("-1");
};

USTRUCT(Blueprintable, BlueprintType)
struct FXGLoginRespData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString UserName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString UserID = TEXT("-1");
};







