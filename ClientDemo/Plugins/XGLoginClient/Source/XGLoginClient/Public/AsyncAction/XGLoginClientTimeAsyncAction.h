// Copyright (c) XiaoGang 2024.All Rights Reserved.

#pragma once

//https://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp
#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"


#include "Kismet/BlueprintAsyncActionBase.h"

#include "XGLoginClientTimeType.h"

#include "XGLoginClientTimeAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FXGLoginClientTimeDelegate, FGuid, AsyncID, bool, bResult, FString, Message, FXGLoginClientTimeRespInfo, RespInfo);


UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientTimeAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	UXGLoginClientTimeAsyncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientTimeAsyncAction();



protected:


	/**
	 * Get network time
	 *
	 * @param WorldContextObject		WolrdContext
	 *
	 * @param InSparkAppID				iFlyTek AppID
	 *
	 *
	 * @return UXGXunFeiSparkAsyncAction* Self object ptr
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientTimeAsyncAction",
		Keywords = "XG Login Client Network Time"),
		Category = "XGLoginClient|NetworkTime")
	static UXGLoginClientTimeAsyncAction* XGLoginClientTimeAsyncAction(UObject* WorldContextObject,
		EXGLoginClientTimeType InLoginClientTimeType,
		FString InYourCustomLoginServerURL);

public:

	virtual void Activate() override;

	virtual void Activate_Internal();


protected:

	void SendHttp(const FString& InServerURL, const FString& InContentString);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGLoginClientTimeRespInfo PRRespInfo);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGLoginClientTimeRespInfo PRRespInfo);

	void RealeaseResources();

public:
	
	UPROPERTY(BlueprintAssignable)
	FXGLoginClientTimeDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientTimeDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientTimeDelegate OnFail;


public:

	FGuid AsyncID = FGuid::NewGuid();
		
	EXGLoginClientTimeType LoginClientTimeType = EXGLoginClientTimeType::TaoBao;

	FString CustomLoginServerURL =TEXT("");

};