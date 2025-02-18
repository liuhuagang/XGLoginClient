// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "XGLoginServerACRespType.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FXGApplyForANewRespData 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString ActiveCode = TEXT("");


};

USTRUCT(Blueprintable, BlueprintType)
struct FXGGetForFreeOneRespData 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString ActiveCode = TEXT("");

};

UENUM(BlueprintType)
enum class EXGActiveCodeSatus: uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Free =1 UMETA(DisplayName = "Free"),
	Lock =2 UMETA(DisplayName = "Lock"),
	Active =3 UMETA(DisplayName = "Active"),
	Invalid =4 UMETA(DisplayName = "Invalid"),

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGActiveCodeInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString ID = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString ActiveCode = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	EXGActiveCodeSatus ActiveCodeStatus = EXGActiveCodeSatus::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FDateTime ActiveCodeTime = FDateTime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FString MachineID = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FDateTime MachineRegisterTime = FDateTime();
};



USTRUCT(Blueprintable, BlueprintType)
struct FXGCheckOneStatusRespData 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	FXGActiveCodeInfo ActiveCodeInfo;
};

USTRUCT(Blueprintable, BlueprintType)
struct FXGGetAllStatusRespData 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|ResponseType")
	TArray<FXGActiveCodeInfo> CodeList ;

};
