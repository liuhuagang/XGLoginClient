// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientLockOneACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXGLoginClientLockOneACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientLockOneACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientLockOneACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientLockOneACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientLockOneACAA",
		Keywords = "XG Login Client Lock One Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientLockOneACAA* XGLoginClientLockOneACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword,
		const FString& InActiveCode);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientLockOneACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientLockOneACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientLockOneACDelegate OnFail;


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

