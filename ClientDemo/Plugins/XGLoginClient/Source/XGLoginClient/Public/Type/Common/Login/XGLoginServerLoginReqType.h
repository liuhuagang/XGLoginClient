// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "XGLoginServerUtil.h"
#include "XGLoginServerRequestType.h"

#include "XGLoginServerLoginReqType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGRegisterReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString UserName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString Password = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString Phone = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString EMail = TEXT("");

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



		if (!FXGLoginServerUtil::CheckPhone(Phone))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegaPhone;
			return false;
		}

		if (!FXGLoginServerUtil::CheckEMail(EMail))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalEMail;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;

		return true;

	}


};

USTRUCT(Blueprintable, BlueprintType)
struct FXGLoginReqData :public FXGLoginServerDataBase
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

