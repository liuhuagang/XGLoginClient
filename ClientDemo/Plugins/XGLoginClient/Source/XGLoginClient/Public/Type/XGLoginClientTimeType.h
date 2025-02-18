// Copyright (c) XiaoGang.2024.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "XGLoginClientTimeType.generated.h"



/**
 * EXGLoginClientTimeType
 * ToDo More URL
 */
UENUM(BlueprintType)
enum class EXGLoginClientTimeType :uint8
{
	TaoBao UMETA(DisplayName = "TaobaoAPI"),
	XGLoginServer UMETA(DisplayName = "XGLoginServerAPI"),
	CustomServer UMETA(DisplayName = "YourCustomLoginServerAPI"),
	MaxNum UMETA(Hidden)
};

/**
 * FXGLoginClientDataInfo
 *
 */
USTRUCT(BlueprintType)
struct XGLOGINCLIENT_API FXGLoginClientTimeRespDataInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FString t = TEXT("");

};





/**
 * FXGLoginClientTimeRespInfo
 *
 */
USTRUCT(BlueprintType)
struct XGLOGINCLIENT_API FXGLoginClientTimeRespMessage
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FString api = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FString v = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	TArray<FString> ret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FXGLoginClientTimeRespDataInfo data ;


};




/**
 * FXGLoginClientTimeRespInfo
 *
 */
USTRUCT(BlueprintType)
struct XGLOGINCLIENT_API FXGLoginClientTimeRespInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FDateTime BeijingDateTime = FDateTime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FDateTime UTCDateTime = FDateTime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FXGLoginClientTimeRespMessage RespMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient|NetworkTime")
	FString RawMessage =TEXT("");


};