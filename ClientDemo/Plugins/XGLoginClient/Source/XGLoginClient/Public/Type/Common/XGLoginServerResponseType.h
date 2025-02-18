// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "XGLoginServerHttpType.h"

#include "XGLoginServerResponseType.generated.h"


UENUM()
enum class EXGLoginServerResponseType : int32
{
	CheckVersionResp,

	RegisterResp,
	LoginResp,

	RegisterWithMachineIDResp,
	LoginWithMachineResp,
	GetRemoteMachineIDAndRegiterTimeResp,

	QueryMoneyResp,
	ConsumeMoneyResp,
	ChargeMoneyResp,

	FirstActiveResp,
	CheckActiveResp,

	ApplyForANewResp,
	GetForFreeOneResp,
	CheckOneStatusResp,
	InvalidOneStatusResp,
	LockOneStatusResp,
	DeleteOneStatusResp,
	GetAllStatusResp,


	MAX,
};

USTRUCT()
struct FXGLoginServerResponse
{
	GENERATED_BODY()

public:

	UPROPERTY()
		bool bResult =false;

	UPROPERTY()
		EXGLoginServerResult ResultType= EXGLoginServerResult::Failed;

	UPROPERTY()
		EXGLoginServerResponseType ResponseType = EXGLoginServerResponseType::MAX;

	UPROPERTY()
		FString Data=TEXT("");

};
