// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientCheckOneStatusACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FXGLoginClientCheckOneStatusACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message,
	FXGActiveCodeInfo,ActiveCodeInfo);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientCheckOneStatusACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientCheckOneStatusACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientCheckOneStatusACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientCheckOneStatusACAA",
		Keywords = "XG Login Client Check One Status Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientCheckOneStatusACAA* XGLoginClientCheckOneStatusACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword,
		const FString& InActiveCode);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckOneStatusACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckOneStatusACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckOneStatusACDelegate OnFail;


protected:

	virtual void Activate_Internal() override;

protected:

	void SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType );

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGActiveCodeInfo InCodeInfo);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage);

	void RealeaseResources();

protected:

	FString ManagerName = TEXT("");

	FString ManagerPassword = TEXT("");

	FString ActiveCode = TEXT("");

	FString ServerIP =TEXT("");

	FString ServerPort = TEXT("");

};

