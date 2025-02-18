// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "XGLoginServerUtil.h"
#include "XGLoginServerRequestType.h"

#include "XGLoginServerACReqType.generated.h"



USTRUCT(Blueprintable, BlueprintType)
struct FXGFirstActiveReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ActiveCode=TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString MachineCode = TEXT("None");


	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{

		if (!FXGLoginServerUtil::CheckActiveCode(ActiveCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllActiveCode;
			return false;
		}



		if (!FXGLoginServerUtil::CheckMachineID(MachineCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllMachineID;
			return false;
		}


		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGCheckActiveReqData :public FXGLoginServerDataBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString MachineCode= TEXT("None");


	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{

		if (!FXGLoginServerUtil::CheckMachineID(MachineCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllMachineID;
			return false;
		}


		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGApplyForANewReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

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

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGGetForFreeOneReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

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

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGCheckOneStatusReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ActiveCode = TEXT("");

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

		if (!FXGLoginServerUtil::CheckActiveCode(ActiveCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllActiveCode;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGInvalidOneStatusReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ActiveCode = TEXT("");

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

		if (!FXGLoginServerUtil::CheckActiveCode(ActiveCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllActiveCode;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGLockOneStatusReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ActiveCode = TEXT("");

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

		if (!FXGLoginServerUtil::CheckActiveCode(ActiveCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllActiveCode;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGDeleteOneStatusReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ActiveCode = TEXT("");

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

		if (!FXGLoginServerUtil::CheckActiveCode(ActiveCode))
		{
			OutRequestDataValidity = EXGLoginServerResult::IllActiveCode;
			return false;
		}

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};

USTRUCT(Blueprintable, BlueprintType)
struct FXGGetAllStatusReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ManagerPassword = TEXT("");

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

		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;

	}

};
