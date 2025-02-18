// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientDeleteOneACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXGLoginClientDeleteOneACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientDeleteOneACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientDeleteOneACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientDeleteOneACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientDeleteOneACAA",
		Keywords = "XG Login Client Delete One Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientDeleteOneACAA* XGLoginClientDeleteOneACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword,
		const FString& InActiveCode);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientDeleteOneACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientDeleteOneACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientDeleteOneACDelegate OnFail;


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

