// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "XGLoginServerUtil.h"
#include "XGLoginServerHttpType.h"

#include "XGLoginServerMoneyReqType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGQueryMoneyReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString UserName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString Password = TEXT("");

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{

		if (!FXGLoginServerUtil::CheckUserName(UserName))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalUserName;
			return false;
		}



		if (!FXGLoginServerUtil::CheckPassword(Password))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegaPassword;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};


USTRUCT(Blueprintable, BlueprintType)
struct FXGConsumeMoneyReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString UserName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString Password = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	float ConsumeMoney = 0.0f;

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{

		if (!FXGLoginServerUtil::CheckUserName(UserName))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalUserName;
			return false;
		}

		if (!FXGLoginServerUtil::CheckPassword(Password))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegaPassword;
			return false;
		}
		if (!FXGLoginServerUtil::CheckConsumeMoney(ConsumeMoney))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllConsumeMoney;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};



USTRUCT(Blueprintable, BlueprintType)
struct FXGChargeMoneyReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString UserName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	float ChargeMoney = 0.0f;

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{

		if (!FXGLoginServerUtil::CheckUserName(ManagerName))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalUserName;
			return false;
		}



		if (!FXGLoginServerUtil::CheckPassword(ManagerPassword))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegaPassword;
			return false;
		}

		if (!FXGLoginServerUtil::CheckUserName(UserName))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalUserName;
			return false;
		}


		if (!FXGLoginServerUtil::CheckChargeMoney(ChargeMoney))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllConsumeMoney;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

