// Copyright 2024 Huagang Liu. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "XGLoginServerHttpType.generated.h"

UENUM()
enum class EXGLoginServerResult : int32
{
	Succeeded,
	Failed,

	ConnectSQLFailed,
	GetWrongSQLResult,

	ParseServerIpAndPortFailed,
	ParseServerResponseFailed,
	ParseServerResponseDataFailed,

	ParseClientRequestFailed,
	ParseClientRequestDataFailed,

	NetError,

	IllToken,
	IllVersion,
	IllReqType,
	IllegalUserName,
	IllegaPassword,
	IllegaPhone,
	IllegalEMail,
	IllMachineID,
	IllConsumeMoney,
	IllChargeMoney,
	IllDateTime,

	RepetitiveName,
	WrongUserNameOrPassword,
	WrongMachineID,
	NoUser,
	NoMachineID,
	NoEnoughBalance,
	NoManagerAuthority,
	UnKnownReqType,

	IllActiveCode,
	IllActiveCodeStatus,
	IllSellTwice,
	IllAlreadyActive,
	NoFreeActiveCode,
	NoTargetActiveCode,
	InvalidTwice,
	LockNoFree,
	NoAnyActiveCode,
	InvalidCode,
	RepetitiveToActive,


	UnKnown,
	MAX

};
