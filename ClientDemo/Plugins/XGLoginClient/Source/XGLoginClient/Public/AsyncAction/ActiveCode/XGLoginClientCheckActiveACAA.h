// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientCheckActiveACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXGLoginClientCheckActiveACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientCheckActiveACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientCheckActiveACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientCheckActiveACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientCheckActiveACAA",
		Keywords = "XG Login Client Check Active Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientCheckActiveACAA* XGLoginClientCheckActiveACAA(UObject* WorldContextObject);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckActiveACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckActiveACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientCheckActiveACDelegate OnFail;


protected:

	virtual void Activate_Internal() override;

protected:

	void SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType);

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage);

	void RealeaseResources();

protected:

	FString MachineID = TEXT("");

	FString ServerIP = TEXT("");

	FString ServerPort = TEXT("");

};

