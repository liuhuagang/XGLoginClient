// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "XGLoginServerUtil.h"
#include "XGLoginServerRequestType.h"
#include "XGLoginServerLoginReqType.h"

#include "XGLoginServerLoginMReqType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGRegisterWithMachineIDReqData :public FXGRegisterReqData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	bool bCustomMachineID = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString MachineID = TEXT("");

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{
		if (!FXGRegisterReqData::IsValid(OutRequestDataValidity))
		{
			return false;
		}

		if (!FXGLoginServerUtil::CheckMachineID(MachineID))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllMachineID;
			return false;
		}


		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}


};
USTRUCT(Blueprintable, BlueprintType)
struct FXGLoginWithMachineIDReqData :public FXGLoginReqData
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	bool bCustomMachineID = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString MachineID = TEXT("");



	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{
		if (!FXGLoginReqData::IsValid(OutRequestDataValidity))
		{
			return false;
		}

		if (!FXGLoginServerUtil::CheckMachineID(MachineID))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllMachineID;
			return false;
		}


		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};
USTRUCT(Blueprintable, BlueprintType)
struct FXGGetRemoteMachineIDAndRegiterTimeReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString UserName = TEXT("");

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{
		if (!FXGLoginServerUtil::CheckUserName(UserName))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllegalUserName;
			return false;
		}
		OutRequestDataValidity = EXGLoginServerResult::Succeeded;

		return true;
	}

};


