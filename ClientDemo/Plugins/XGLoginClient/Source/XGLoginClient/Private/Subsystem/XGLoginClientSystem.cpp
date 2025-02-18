// Copyright (c) XiaoGang.2023.All Rights Reserved.

#include "XGLoginClientSystem.h"

#include "Kismet/KismetSystemLibrary.h"
#include "JsonObjectConverter.h"

#include "LogXGLoginClient.h"
#include "XGLoginClientSettings.h"

#include "XGLoginClientBPLibrary.h"

void UXGLoginClientSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UXGLoginClientSystem::Deinitialize()
{
	Super::Deinitialize();
}

FGuid UXGLoginClientSystem::CheckVersion(FXGCheckVersionDelegate CheckVersionDelegate)
{
	EXGLoginServerResult ResponseResult;

	FGuid DelegateGuid = FGuid::NewGuid();


	//1.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		CheckVersionDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult));
		return DelegateGuid;
	}


	//2.收集版本信息
	FString RequestData = TEXT("");
	FXGCheckVersionReqData CheckVersionReqData;
	CheckVersionReqData.ClientVersion = UXGLoginClientSettings::GetXGLoginServerSettings()->ClientVersion;
	FJsonObjectConverter::UStructToJsonObjectString(CheckVersionReqData, RequestData);

	//3.记录代理
	CheckVersionDelegatesMap.Add(DelegateGuid, CheckVersionDelegate);

	//4.发出版本校验申请请求
	SendHttp(EXGLoginRequestType::CheckVersionReq, RequestData, DelegateGuid);


	return DelegateGuid;
}

FGuid UXGLoginClientSystem::Register(FXGRegisterReqData RegisterReqData, FXGRegisterDelegate RegisterDelegate)
{
	EXGLoginServerResult ResponseResult;

	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否
	bool bRightRegister = RegisterReqData.IsValid(ResponseResult);

	if (!bRightRegister)
	{
		FXGRegisterRespData RegisterRespData;
		RegisterDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RegisterRespData);
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGRegisterRespData RegisterRespData;
		RegisterDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RegisterRespData);
		return DelegateGuid;
	}
	//3.添加代理
	RegisterDelegates.Add(DelegateGuid, RegisterDelegate);

	//4.反序列化数据
	RegisterReqData.Password = MD5HashPassword(RegisterReqData.Password);

	FString RegisterDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(RegisterReqData, RegisterDataStr);
	//5.发出注册请求
	SendHttp(EXGLoginRequestType::RegisterReq, RegisterDataStr, DelegateGuid);


	return DelegateGuid;
}

FGuid UXGLoginClientSystem::Login(FXGLoginReqData LoginReqData, FXGLoginDelegate LoginDelegate)
{
	EXGLoginServerResult ResponseResult;

	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否


	bool bRightRegister = LoginReqData.IsValid(ResponseResult);
	if (!bRightRegister)
	{
		FXGLoginRespData LoginRespData;
		LoginDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), LoginRespData);
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGLoginRespData LoginRespData;
		LoginDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), LoginRespData);
		return DelegateGuid;
	}

	//3.本地记录代理,等待服务端回调

	LoginDelegates.Add(DelegateGuid, LoginDelegate);

	//4.反序列化数据
	LoginReqData.Password = MD5HashPassword(LoginReqData.Password);

	FString LoginReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(LoginReqData, LoginReqDataStr);


	//5.发出登录请求
	SendHttp(EXGLoginRequestType::LoginReq, LoginReqDataStr, DelegateGuid);

	return DelegateGuid;
}


FGuid UXGLoginClientSystem::RegisterWithMachineID(FXGRegisterWithMachineIDReqData RegisterWithMachineIDReqData, FXGRegisterDelegate RegisterDelegate)
{
	EXGLoginServerResult ResponseResult;
	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否

	if (!RegisterWithMachineIDReqData.bCustomMachineID)
	{
		RegisterWithMachineIDReqData.MachineID= UXGLoginClientBPLibrary::XGGetOperatingSystemId();
	}

	bool bRightRegister = RegisterWithMachineIDReqData.IsValid(ResponseResult);

	if (!bRightRegister)
	{
		FXGRegisterRespData RegisterRespData;
		RegisterDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RegisterRespData);
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGRegisterRespData RegisterRespData;
		RegisterDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RegisterRespData);
		return DelegateGuid;
	}

	//3.本地记录代理,等待服务端回调

	RegisterDelegates.Add(DelegateGuid, RegisterDelegate);

	//4.反序列化数据
	RegisterWithMachineIDReqData.Password = MD5HashPassword(RegisterWithMachineIDReqData.Password);



	FString RegisterDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(RegisterWithMachineIDReqData, RegisterDataStr);

	//5.发出注册请求
	SendHttp(EXGLoginRequestType::RegisterWithMachineReq, RegisterDataStr, DelegateGuid);

	return DelegateGuid;
}

FGuid UXGLoginClientSystem::LoginWithMachineID(FXGLoginWithMachineIDReqData LoginWithMachineIDReqData, FXGLoginDelegate LoginDelegate)
{
	EXGLoginServerResult ResponseResult;
	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否
	if (!LoginWithMachineIDReqData.bCustomMachineID)
	{
		LoginWithMachineIDReqData.MachineID = UXGLoginClientBPLibrary::XGGetOperatingSystemId();
	}


	bool bRightLoginData = LoginWithMachineIDReqData.IsValid(ResponseResult);
	if (!bRightLoginData)
	{
		FXGLoginRespData LoginRespData;
		LoginDelegate.ExecuteIfBound(DelegateGuid ,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), LoginRespData);
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGLoginRespData LoginRespData;
		LoginDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), LoginRespData);
		return DelegateGuid;
	}

	//3.本地记录代理,等待服务端回调
	LoginDelegates.Add(DelegateGuid, LoginDelegate);

	//4.反序列化数据
	LoginWithMachineIDReqData.Password = MD5HashPassword(LoginWithMachineIDReqData.Password);

	FString LoginReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(LoginWithMachineIDReqData, LoginReqDataStr);


	//5.发出登录请求
	SendHttp(EXGLoginRequestType::LoginWithMachineReq, LoginReqDataStr, DelegateGuid);

	return DelegateGuid;
}

FGuid UXGLoginClientSystem::GetRemoteMachineIDAndRegiterTime(
	 FXGGetRemoteMachineIDAndRegiterTimeReqData GetRemoteMachineIDAndRegiterTimeReqData,
	FXGGetMachineAndRegisterTimeDelegate GetMachineAndRegister)
{
	EXGLoginServerResult ResponseResult;
	FGuid DeleteGuid = FGuid::NewGuid();


	if (!GetRemoteMachineIDAndRegiterTimeReqData.IsValid(ResponseResult))
	{
		FXGGetMachineAndRegisterTimeRespData GetMachineAndRegisterTimeRespData;
		GetMachineAndRegister.ExecuteIfBound(DeleteGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), GetMachineAndRegisterTimeRespData);
		
		return DeleteGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGGetMachineAndRegisterTimeRespData GetMachineAndRegisterTimeRespData;
		GetMachineAndRegister.ExecuteIfBound(DeleteGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), GetMachineAndRegisterTimeRespData);

		return DeleteGuid;
	}

	//3.本地记录代理,等待服务端回调

	GetMachineAndRegisterTimeDelegates.Add(DeleteGuid, GetMachineAndRegister);

	//4.反序列化数据
	FString GetMachineAndRegisterTimeReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(GetRemoteMachineIDAndRegiterTimeReqData, GetMachineAndRegisterTimeReqDataStr);

	//5.发出登录请求
	SendHttp(EXGLoginRequestType::GetRemoteMachineIDAndRegiterTimeReq, GetMachineAndRegisterTimeReqDataStr, DeleteGuid);

	return DeleteGuid;
}

FGuid UXGLoginClientSystem::QueryMoney(FXGQueryMoneyReqData QueryMoneyReqData, FXGQueryMoneyDelegate QueryMoneyDeletgate)
{
	EXGLoginServerResult ResponseResult;
	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否


	bool bRightData = QueryMoneyReqData.IsValid(ResponseResult);
	if (!bRightData)
	{
		FXGQueryMoneyRespData QueryMoneyRespData;
		QueryMoneyDeletgate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), QueryMoneyRespData);

		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGQueryMoneyRespData QueryMoneyRespData;
		QueryMoneyDeletgate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), QueryMoneyRespData);

		return DelegateGuid;
	}



	//3.本地记录代理,等待服务端回调

	QueryMoneyDeletgates.Add(DelegateGuid, QueryMoneyDeletgate);

	//4.反序列化数据
	QueryMoneyReqData.Password = MD5HashPassword(QueryMoneyReqData.Password);

	FString ReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(QueryMoneyReqData, ReqDataStr);


	//5.发出登录请求
	SendHttp(EXGLoginRequestType::QueryMoneyReq, ReqDataStr, DelegateGuid);


	return DelegateGuid;

}

FGuid UXGLoginClientSystem::ConsumeMoney(FXGConsumeMoneyReqData ConsumeMoneyReqData, FXGConsumeMoneyDelegate ComsumeMoneyDelegate)
{
	//1.校验数据正确与否
	EXGLoginServerResult ResponseResult;
	FGuid DelegateGuid = FGuid::NewGuid();

	bool bRightData = ConsumeMoneyReqData.IsValid(ResponseResult);
	if (!bRightData)
	{
		FXGConsumeMoneyRespData RespData;
		ComsumeMoneyDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RespData);
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGConsumeMoneyRespData RespData;
		ComsumeMoneyDelegate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RespData);
		return DelegateGuid;
	}



	//3.本地记录代理,等待服务端回调

	ComsumeMoneyDelegates.Add(DelegateGuid, ComsumeMoneyDelegate);

	//4.反序列化数据
	ConsumeMoneyReqData.Password = MD5HashPassword(ConsumeMoneyReqData.Password);

	FString ReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(ConsumeMoneyReqData, ReqDataStr);


	//5.发出登录请求
	SendHttp(EXGLoginRequestType::ConsumeMoneyReq, ReqDataStr, DelegateGuid);

	return DelegateGuid;
}

FGuid UXGLoginClientSystem::ChargeMoney(FXGChargeMoneyReqData ChargeMoneyReqData, FXGChargeMoneylegate ChargeMoneyDeletgate)
{
	EXGLoginServerResult ResponseResult;
	FGuid DelegateGuid = FGuid::NewGuid();

	//1.校验数据正确与否

	bool bRightData = ChargeMoneyReqData.IsValid(ResponseResult);
	if (!bRightData)
	{
		FXGChargeMoneyRespData RespData;
		ChargeMoneyDeletgate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RespData);
		
		return DelegateGuid;
	}

	//2.获取本地配置的远端服务器信息
	if (!LoadXGLoginServerIPAndPort())
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		FXGChargeMoneyRespData RespData;
		ChargeMoneyDeletgate.ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult), RespData);
		
		return DelegateGuid;
	}



	//3.本地记录代理,等待服务端回调

	ChargeMoneyDeletgates.Add(DelegateGuid, ChargeMoneyDeletgate);

	//4.反序列化数据
	ChargeMoneyReqData.ManagerPassword = MD5HashPassword(ChargeMoneyReqData.ManagerPassword);

	FString ReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(ChargeMoneyReqData, ReqDataStr);


	//5.发出登录请求
	SendHttp(EXGLoginRequestType::ChargeMoneyReq, ReqDataStr, DelegateGuid);

	return DelegateGuid;


}

void UXGLoginClientSystem::SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr, const FGuid& InDelegateGuid)
{

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	FXGLoginServerRequest XGLoginServerRequest;
	XGLoginServerRequest.RequestType = InRequestType;
	XGLoginServerRequest.Data = InRequestDataStr;

	FString RequestBody;
	FJsonObjectConverter::UStructToJsonObjectString(XGLoginServerRequest, RequestBody);

	Request->OnProcessRequestComplete().BindUObject(this, &UXGLoginClientSystem::OnResponseReceived, XGLoginServerRequest.RequestType, InDelegateGuid);

	FString URL = FString::Printf(TEXT("http://%s:%s/Login"), *XGLoginServerIP, *XGLoginServerPort);
	Request->SetURL(URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("XGLoginServerToken", TCHAR_TO_ANSI(*GenerateToken()));
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();
}

void UXGLoginClientSystem::OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType, FGuid DelegateGuid)
{
	EXGLoginServerResult ServerResult = EXGLoginServerResult::NetError;

	if (bSucceeded && HttpRequest->GetStatus() == EHttpRequestStatus::Succeeded && HttpResponse->GetResponseCode() == 200)
	{
		UE_LOG(LogXGLoginClient, Display, TEXT("[%s]"), *FString(__FUNCTION__));

		FString ResponseJson = HttpResponse->GetContentAsString();
		FXGLoginServerResponse  XGLoginServerResponse;

		if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseJson, &XGLoginServerResponse))
		{
			if (XGLoginServerResponse.ResultType == EXGLoginServerResult::Succeeded)
			{
				ProcessHttpResponse(XGLoginServerResponse, DelegateGuid);
				return;
			}
			else
			{
				ServerResult = XGLoginServerResponse.ResultType;
			}

		}
		else
		{
			ServerResult = EXGLoginServerResult::ParseServerResponseFailed;
		}
	}


	switch (RequestType)
	{
	case EXGLoginRequestType::CheckVersionReq:
		if (CheckVersionDelegatesMap.Num() > 0)
		{
			if (FXGCheckVersionDelegate* CheckVersionDelegate = CheckVersionDelegatesMap.Find(DelegateGuid))
			{

				CheckVersionDelegate->ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult));
				CheckVersionDelegatesMap.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::RegisterReq:

		if (RegisterDelegates.Num() > 0)
		{
			if (FXGRegisterDelegate* RegisterDelegate = RegisterDelegates.Find(DelegateGuid))
			{
				FXGRegisterRespData RegisterRespData;
				RegisterDelegate->ExecuteIfBound(DelegateGuid,false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RegisterRespData);
				RegisterDelegates.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::LoginReq:

		if (LoginDelegates.Num() > 0)
		{
			if (FXGLoginDelegate* LoginDelegate = LoginDelegates.Find(DelegateGuid))
			{
				FXGLoginRespData LoginRespData;
				LoginDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), LoginRespData);
				LoginDelegates.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::RegisterWithMachineReq:

		if (RegisterDelegates.Num() > 0)
		{
			if (FXGRegisterDelegate* RegisterDelegate = RegisterDelegates.Find(DelegateGuid))
			{
				FXGRegisterRespData RegisterRespData;
				RegisterDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RegisterRespData);
				RegisterDelegates.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::LoginWithMachineReq:

		if (LoginDelegates.Num() > 0)
		{
			if (FXGLoginDelegate* LoginDelegate = LoginDelegates.Find(DelegateGuid))
			{
				FXGLoginRespData LoginRespData;
				LoginDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), LoginRespData);
				LoginDelegates.Remove(DelegateGuid);
			}
		}

		break;

	case EXGLoginRequestType::GetRemoteMachineIDAndRegiterTimeReq:

		if (GetMachineAndRegisterTimeDelegates.Num() > 0)
		{
			if (FXGGetMachineAndRegisterTimeDelegate* GetMachineAndRegisterTimeDelegate = GetMachineAndRegisterTimeDelegates.Find(DelegateGuid))
			{
				FXGGetMachineAndRegisterTimeRespData GetMachineAndRegisterTimeRespData;

				GetMachineAndRegisterTimeDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), GetMachineAndRegisterTimeRespData);
				GetMachineAndRegisterTimeDelegates.Remove(DelegateGuid);
			}
		}

		break;

	case EXGLoginRequestType::QueryMoneyReq:

		if (QueryMoneyDeletgates.Num() > 0)
		{
			if (FXGQueryMoneyDelegate* QueryMoneyDelegateDelegate = QueryMoneyDeletgates.Find(DelegateGuid))
			{
				FXGQueryMoneyRespData RespData;

				QueryMoneyDelegateDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RespData);
				QueryMoneyDeletgates.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::ConsumeMoneyReq:

		if (ComsumeMoneyDelegates.Num() > 0)
		{
			if (FXGConsumeMoneyDelegate* ComsumeMoneyDelegate = ComsumeMoneyDelegates.Find(DelegateGuid))
			{
				FXGConsumeMoneyRespData RespData;

				ComsumeMoneyDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RespData);
				ComsumeMoneyDelegates.Remove(DelegateGuid);
			}
		}

		break;
	case EXGLoginRequestType::ChargeMoneyReq:

		if (ChargeMoneyDeletgates.Num() > 0)
		{
			if (FXGChargeMoneylegate* ChargeMoneyDeletgate = ChargeMoneyDeletgates.Find(DelegateGuid))
			{
				FXGChargeMoneyRespData RespData;

				ChargeMoneyDeletgate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RespData);
				ChargeMoneyDeletgates.Remove(DelegateGuid);
			}
		}

		break;

		break;
	





	case EXGLoginRequestType::MAX:
		break;
	default:
		break;
	}


}

void UXGLoginClientSystem::ProcessHttpResponse(const FXGLoginServerResponse& LoginServerResponse, const FGuid& DelegateGuid)
{

	switch (LoginServerResponse.ResponseType)
	{

	case EXGLoginServerResponseType::CheckVersionResp:
		if (CheckVersionDelegatesMap.Num() > 0)
		{
			if (FXGCheckVersionDelegate* CheckVersionDelegate = CheckVersionDelegatesMap.Find(DelegateGuid))
			{
				CheckVersionDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType));
				CheckVersionDelegatesMap.Remove(DelegateGuid);
			}


		}

		break;

	case EXGLoginServerResponseType::RegisterResp:

		if (RegisterDelegates.Num() > 0)
		{
			if (FXGRegisterDelegate* RegisterDelegate = RegisterDelegates.Find(DelegateGuid))
			{
				FXGRegisterRespData RegisterRespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &RegisterRespData))
				{
					RegisterDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType), RegisterRespData);
				}
				else
				{
					RegisterDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), RegisterRespData);
				}
				RegisterDelegates.Remove(DelegateGuid);
			}
		}


		break;
	case EXGLoginServerResponseType::LoginResp:
		if (LoginDelegates.Num() > 0)
		{
			if (FXGLoginDelegate* LoginDelegate = LoginDelegates.Find(DelegateGuid))
			{
				FXGLoginRespData LoginRespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &LoginRespData))
				{
					LoginDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType), LoginRespData);
				}
				else
				{
					LoginDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), LoginRespData);
				}
				LoginDelegates.Remove(DelegateGuid);
			}
		}
		break;
	case EXGLoginServerResponseType::GetRemoteMachineIDAndRegiterTimeResp:

		if (GetMachineAndRegisterTimeDelegates.Num() > 0)
		{
			if (FXGGetMachineAndRegisterTimeDelegate* GetMachineAndRegisterTimeDelegate = GetMachineAndRegisterTimeDelegates.Find(DelegateGuid))
			{
				FXGGetMachineAndRegisterTimeRespData GetMachineAndRegisterTimeRespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &GetMachineAndRegisterTimeRespData))
				{
					GetMachineAndRegisterTimeDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType), GetMachineAndRegisterTimeRespData);
				}
				else
				{
					GetMachineAndRegisterTimeDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), GetMachineAndRegisterTimeRespData);
				}
				GetMachineAndRegisterTimeDelegates.Remove(DelegateGuid);
			}
		}


		break;


	case EXGLoginServerResponseType::QueryMoneyResp:

		if (QueryMoneyDeletgates.Num() > 0)
		{
			if (FXGQueryMoneyDelegate* QueryMoneyDelegate = QueryMoneyDeletgates.Find(DelegateGuid))
			{
				FXGQueryMoneyRespData RespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &RespData))
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType), RespData);
				}
				else
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), RespData);
				}
				QueryMoneyDeletgates.Remove(DelegateGuid);
			}
		}
		break;
	case EXGLoginServerResponseType::ConsumeMoneyResp:
		if (ComsumeMoneyDelegates.Num() > 0)
		{
			if (FXGConsumeMoneyDelegate* QueryMoneyDelegate = ComsumeMoneyDelegates.Find(DelegateGuid))
			{
				FXGConsumeMoneyRespData RespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &RespData))
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType), RespData);
				}
				else
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), RespData);
				}
				ComsumeMoneyDelegates.Remove(DelegateGuid);
			}
		}
		break;
	case EXGLoginServerResponseType::ChargeMoneyResp:
		if (ChargeMoneyDeletgates.Num() > 0)
		{
			if (FXGChargeMoneylegate* QueryMoneyDelegate = ChargeMoneyDeletgates.Find(DelegateGuid))
			{
				FXGChargeMoneyRespData RespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(LoginServerResponse.Data, &RespData))
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, LoginServerResponse.bResult, FXGLoginServerUtil::XGLoginServerResultToString(LoginServerResponse.ResultType) , RespData);
				}
				else
				{
					QueryMoneyDelegate->ExecuteIfBound(DelegateGuid, false, FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult::ParseServerResponseDataFailed), RespData);
				}
				ChargeMoneyDeletgates.Remove(DelegateGuid);
			}
		}
		break;



	default:
		break;
	}

}


bool UXGLoginClientSystem::LoadXGLoginServerIPAndPort()
{
	return UXGLoginClientSettings::GetXGLoginServerSettings()->LoadXGLoginServerIPAndPort(XGLoginServerIP, XGLoginServerPort);
}

bool UXGLoginClientSystem::LoadMD5TokenAndNum(FString& Token, int32& HashNum)
{
	if (UXGLoginClientSettings* LoginClientSettings = UXGLoginClientSettings::GetXGLoginServerSettings())
	{
		Token = LoginClientSettings->Token;
		HashNum = LoginClientSettings->HashNum;
		return true;
	}

	return  false;


	//FConfigFile DatabaseConfig;
	//FString Path = FPaths::ProjectConfigDir() / TEXT("DefaultDataBase.ini");
	//DatabaseConfig.Read(Path);

	//bool bHashNum = DatabaseConfig.GetInt(TEXT("/Script/XGLoginClient.DataBaseSettings"), TEXT("HashNum"), HashNum);
	//bool bToken = DatabaseConfig.GetString(TEXT("/Script/XGLoginClient.DataBaseSettings"), TEXT("Token"), Token);

	//if (bHashNum && bToken)
	//{

	//	return true;
	//}

}

FString UXGLoginClientSystem::GenerateToken()
{
	FString ClientToken = TEXT("123456");
	int32  MD5Num;
	if (LoadMD5TokenAndNum(ClientToken, MD5Num))
	{
		int32 CurrentHour = FDateTime::Now().GetMonth();
		//	ClientToken = ClientToken + TEXT("||") + FString::FromInt(CurrentHour);

		for (int32 Index = 0; Index < MD5Num; Index++)
		{
			ClientToken = FMD5::HashAnsiString(*ClientToken);

		}


	}

	return ClientToken;
}

bool UXGLoginClientSystem::CheckToken(FString InToken)
{

	FString ClientToken = TEXT("123456");
	int32  MD5Num;
	if (!LoadMD5TokenAndNum(ClientToken, MD5Num))
	{

		return false;

	}
	else
	{
		/*
				int32 CurrentDay = FDateTime::Now().GetMonth();
				int32 LastDay = CurrentDay - 1;
				int32 NextDay = CurrentDay + 1;

				if (LastDay == 0)
				{
					LastDay = 12;
				}
				if (NextDay == 13)
				{
					NextDay = 1;
				}

				FString ClientToken1 = ClientToken + TEXT("||") + FString::FromInt(CurrentDay);
				FString ClientToken2 = ClientToken + TEXT("||") + FString::FromInt(LastDay);
				FString ClientToken3 = ClientToken + TEXT("||") + FString::FromInt(NextDay);

				for (int32 Index = 0; Index < MD5Num; Index++)
				{
					ClientToken1 = FMD5::HashAnsiString(*ClientToken1);
					ClientToken2 = FMD5::HashAnsiString(*ClientToken2);
					ClientToken3 = FMD5::HashAnsiString(*ClientToken3);
				}
				if (InToken.Equals(ClientToken1) || InToken.Equals(ClientToken2) || InToken.Equals(ClientToken3))
				{
					return true;
				}*/
		for (int32 Index = 0; Index < MD5Num; Index++)
		{
			ClientToken = FMD5::HashAnsiString(*ClientToken);

		}

		if (InToken.Equals(ClientToken))
		{
			return true;
		}

	}

	return false;

}

FString UXGLoginClientSystem::MD5HashPassword(FString InPassword)
{

	FString	HashString = FMD5::HashAnsiString(*InPassword);
	return HashString;
}


