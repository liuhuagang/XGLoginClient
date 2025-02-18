// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"


#include "XGLoginServerHttpType.h"

#include "XGLoginServerMoneyRespType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGQueryMoneyRespData 
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserName=TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserID = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		float Balance=0.f;

};



USTRUCT(Blueprintable, BlueprintType)
struct FXGConsumeMoneyRespData 
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserName=TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserID = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		float ConsumeMoney=0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		float Balance=0.f;

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGChargeMoneyRespData  
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		FString UserID = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		float ChargeMoney=0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
		float Balance=0.f;

};