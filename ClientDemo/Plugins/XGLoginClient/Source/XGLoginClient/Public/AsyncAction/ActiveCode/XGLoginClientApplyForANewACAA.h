// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientApplyForANewACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXGLoginClientApplyForANewACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientApplyForANewACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientApplyForANewACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientApplyForANewACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientApplyForANewACAA",
		Keywords = "XG Login Client Apply For A New Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientApplyForANewACAA* XGLoginClientApplyForANewACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientApplyForANewACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientApplyForANewACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientApplyForANewACDelegate OnFail;


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

	FString ServerIP =TEXT("");

	FString ServerPort = TEXT("");

};

