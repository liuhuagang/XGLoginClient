// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "XGLoginServerUtil.h"
#include "XGLoginServerHttpType.h"

#include "XGLoginServerRequestType.generated.h"



UENUM()
enum class EXGLoginRequestType : int32
{
	CheckVersionReq,
	RegisterReq,
	LoginReq,

	RegisterWithMachineReq,
	LoginWithMachineReq,
	GetRemoteMachineIDAndRegiterTimeReq,

	QueryMoneyReq,
	ConsumeMoneyReq,
	ChargeMoneyReq,

	FirstActiveReq,
	CheckActiveReq,

	ApplyForANewReq,
	GetForFreeOneReq,
	CheckOneStatusReq,
	InvalidOneStatusReq,
	LockOneStatusReq,
	DeleteOneStatusReq,
	GetAllStatusReq,

	MAX
};


USTRUCT()
struct FXGLoginServerRequest
{
	GENERATED_BODY()

public:

	UPROPERTY()
	EXGLoginRequestType RequestType = EXGLoginRequestType::MAX;

	UPROPERTY()
	FString Data = TEXT("");

};

USTRUCT()
struct FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	FXGLoginServerDataBase() {}

	virtual ~FXGLoginServerDataBase() {}

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const { return false; };

};


