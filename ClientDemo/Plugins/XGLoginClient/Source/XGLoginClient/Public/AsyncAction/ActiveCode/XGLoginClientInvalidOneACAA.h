// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientInvalidOneACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXGLoginClientInvalidOneACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientInvalidOneACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientInvalidOneACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientInvalidOneACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientInvalidOneACAA",
		Keywords = "XG Login Client Invalid One Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientInvalidOneACAA* XGLoginClientInvalidOneACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword,
		const FString& InActiveCode);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientInvalidOneACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientInvalidOneACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientInvalidOneACDelegate OnFail;


protected:

	virtual void Activate_Internal() override;

protected:

	void SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType );

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage);

	void RealeaseResources();

protected:

	FString ManagerName = TEXT("");

	FString ManagerPassword = TEXT("");

	FString ActiveCode = TEXT("");

	FString ServerIP =TEXT("");

	FString ServerPort = TEXT("");

};

