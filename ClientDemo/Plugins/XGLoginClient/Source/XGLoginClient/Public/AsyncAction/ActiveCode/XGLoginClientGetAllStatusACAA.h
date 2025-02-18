// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBaseAsyncAction.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginClientGetAllStatusACAA.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FXGLoginClientGetAllStatusACDelegate,
	FGuid, AsyncID,
	bool, bResult,
	FString, Message,
	const TArray<FXGActiveCodeInfo>& , CodeList);



UCLASS(meta = (HideThen = true))
class XGLOGINCLIENT_API UXGLoginClientGetAllStatusACAA : public UXGLoginClientBaseAsyncAction
{
	GENERATED_BODY()

public:

	UXGLoginClientGetAllStatusACAA(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ~UXGLoginClientGetAllStatusACAA();

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true",
		WorldContext = "WorldContextObject",
		DisplayName = "XGLoginClientGetAllStatusACAA",
		Keywords = "XG Login Client Get All Status Active Code Async Action"),
		Category = "XGLoginClient|ActiveCode")
	static UXGLoginClientGetAllStatusACAA* XGLoginClientGetAllStatusACAA(UObject* WorldContextObject,
		const FString& InManagerName,
		const FString& InManagerPassword);

	virtual void Activate() override;

public:


	UPROPERTY(BlueprintAssignable)
	FXGLoginClientGetAllStatusACDelegate Then;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientGetAllStatusACDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FXGLoginClientGetAllStatusACDelegate OnFail;


protected:

	virtual void Activate_Internal() override;

protected:

	void SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr);

	void OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType);

	void CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, TArray<FXGActiveCodeInfo> InCodeList);

	void CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage);

	void RealeaseResources();

protected:

	FString ManagerName = TEXT("");

	FString ManagerPassword = TEXT("");

	FString ServerIP = TEXT("");

	FString ServerPort = TEXT("");

};

