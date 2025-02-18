// Copyright (c) XiaoGang.2023.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "XGLoginClientBPLibrary.h"
#include "XGLoginServerRequestType.h"
#include "XGLoginServerResponseType.h"

#include "XGLoginServerACReqType.h"
#include "XGLoginServerACRespType.h"

#include "XGLoginServerCVReqType.h"
#include "XGLoginServerCVRespType.h"

#include "XGLoginServerLoginReqType.h"
#include "XGLoginServerLoginRespType.h"

#include "XGLoginServerLoginMReqType.h"
#include "XGLoginServerLoginMRespType.h"

#include "XGLoginServerMoneyReqType.h"
#include "XGLoginServerMoneyRespType.h"


#include "XGLoginClientSystem.generated.h"


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FXGCheckVersionDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType);

DECLARE_DYNAMIC_DELEGATE_FourParams(FXGRegisterDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGRegisterRespData&, RegisterRespData);
DECLARE_DYNAMIC_DELEGATE_FourParams(FXGLoginDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGLoginRespData&, LoginRespData);

DECLARE_DYNAMIC_DELEGATE_FourParams(FXGGetMachineAndRegisterTimeDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGGetMachineAndRegisterTimeRespData&, MachineRegisterTimeRespData);

DECLARE_DYNAMIC_DELEGATE_FourParams(FXGQueryMoneyDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGQueryMoneyRespData&, QueryMoneyRespData);
DECLARE_DYNAMIC_DELEGATE_FourParams(FXGConsumeMoneyDelegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGConsumeMoneyRespData&, ConsumeMoneyRespData);
DECLARE_DYNAMIC_DELEGATE_FourParams(FXGChargeMoneylegate, FGuid, AsyncID, bool, bResult, const FString&, ResponseType, const FXGChargeMoneyRespData&, ChargeMoneyRespData);




UCLASS()
class XGLOGINCLIENT_API UXGLoginClientSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	virtual void Initialize(FSubsystemCollectionBase& Collection)override;

	virtual void Deinitialize()override;

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteCheck",
		Keywords = "XGLoginClient Execute Check Version"), Category = "XGLoginClient|Common")
	FGuid CheckVersion(FXGCheckVersionDelegate  CheckVersionDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteRegister",
		Keywords = "XGLoginClient Execute Register"), Category = "XGLoginClient|Simple")
	FGuid Register( FXGRegisterReqData  UserRegisterData, FXGRegisterDelegate RegisterDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteLogin",
		Keywords = "XGLoginClient Execute Login"), Category = "XGLoginClient|Simple")
	FGuid Login( FXGLoginReqData LoginReqData, FXGLoginDelegate LoginDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteRegisterWithMachineID",
		Keywords = "XGLoginClient Execute Register"), Category = "XGLoginClient|Machine")
	FGuid RegisterWithMachineID(FXGRegisterWithMachineIDReqData RegisterWithMachineIDReqData,
		FXGRegisterDelegate RegisterDelegate);

	UFUNCTION(BlueprintCallable,meta = (DisplayName = "ExecuteLoginWithMachineID",
	Keywords = "XGLoginClient Execute Login"),Category = "XGLoginClient|Machine")
	FGuid LoginWithMachineID(FXGLoginWithMachineIDReqData LoginWithMachineIDReqData,
		FXGLoginDelegate LoginDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteGetRemoteMachineIDAndRegiterTime",
		Keywords = "XGLoginClient Execute Machine ID"), Category = "XGLoginClient|Machine")
	FGuid GetRemoteMachineIDAndRegiterTime(FXGGetRemoteMachineIDAndRegiterTimeReqData GetRemoteMachineIDAndRegiterTimeReqData,
		FXGGetMachineAndRegisterTimeDelegate GetMachineAndRegister);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteQueryMoney",
		Keywords = "XGLoginClient Execute Query Money"), Category = "XGLoginClient|Simple")
	FGuid QueryMoney(FXGQueryMoneyReqData QueryMoneyReqData, FXGQueryMoneyDelegate QueryMoneyDeletgate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteConsumeMoney",
		Keywords = "XGLoginClient Execute Comsume Money"), Category = "XGLoginClient|Simple")
	FGuid ConsumeMoney(FXGConsumeMoneyReqData ConsumeMoneyReqData, FXGConsumeMoneyDelegate ComsumeMoneyDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExecuteChargeMoney",
		Keywords = "XGLoginClient Execute Charge Money"), Category = "XGLoginClient|Simple")
	FGuid ChargeMoney(FXGChargeMoneyReqData ChargeMoneyReqData, FXGChargeMoneylegate ChargeMoneyDeletgate);

protected:

	void SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr, const FGuid& InDelegateGuid);
	void OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType, FGuid DelegateGuid);
	void ProcessHttpResponse(const FXGLoginServerResponse& LoginServerResponse, const  FGuid& DelegateGuid);

protected:
	bool LoadXGLoginServerIPAndPort();
	bool LoadMD5TokenAndNum(FString& Token, int32& HashNum);
	FString GenerateToken();
	bool CheckToken(FString InToken);
	FString MD5HashPassword(FString InPassword);

protected:

	FString XGLoginServerIP;
	FString XGLoginServerPort;

	TMap<FGuid, FXGCheckVersionDelegate> CheckVersionDelegatesMap;
	TMap<FGuid, FXGRegisterDelegate> RegisterDelegates;
	TMap<FGuid, FXGLoginDelegate> LoginDelegates;

	TMap<FGuid, FXGGetMachineAndRegisterTimeDelegate> GetMachineAndRegisterTimeDelegates;

	TMap<FGuid, FXGQueryMoneyDelegate> QueryMoneyDeletgates;
	TMap<FGuid, FXGConsumeMoneyDelegate> ComsumeMoneyDelegates;
	TMap<FGuid, FXGChargeMoneylegate> ChargeMoneyDeletgates;


};