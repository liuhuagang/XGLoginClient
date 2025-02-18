// Copyright 2025 Huagang Liu. All Rights Reserved.

#include "XGLoginClientCheckOneStatusACAA.h"

#include "JsonObjectConverter.h"
#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"

#include "XGLoginClientSettings.h"
#include "Log/LogXGLoginClient.h"
#include "XGLoginServerRequestType.h"
#include "XGLoginServerResponseType.h"
#include "XGLoginServerUtil.h"

UXGLoginClientCheckOneStatusACAA::UXGLoginClientCheckOneStatusACAA(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{

}

UXGLoginClientCheckOneStatusACAA::~UXGLoginClientCheckOneStatusACAA()
{
	RealeaseResources();
}

UXGLoginClientCheckOneStatusACAA* UXGLoginClientCheckOneStatusACAA::XGLoginClientCheckOneStatusACAA(UObject* WorldContextObject,
const FString& InManagerName,
const FString& InManagerPassword,
const FString& InActiveCode)
{
	UXGLoginClientCheckOneStatusACAA* AsyncAction = NewObject<UXGLoginClientCheckOneStatusACAA>();

	AsyncAction->ManagerName = InManagerName;
	AsyncAction->ManagerPassword = InManagerPassword;
	AsyncAction->ActiveCode = InActiveCode;

	AsyncAction->RegisterWithGameInstance(WorldContextObject);

	return AsyncAction;
}

void UXGLoginClientCheckOneStatusACAA::Activate()
{
	Super::Activate();

	Then.Broadcast(AsyncID, false,
		TEXT("XGLoginClientCheckOneStatusACAA is just started,please wait to be finished!"), FXGActiveCodeInfo());

}

void UXGLoginClientCheckOneStatusACAA::Activate_Internal()
{

	EXGLoginServerResult ResponseResult;

	//1.校验数据正确与否
	FXGCheckOneStatusReqData ReqData;

	ReqData.ManagerName = ManagerName;
	ReqData.ManagerPassword = ManagerPassword ;
	ReqData.ActiveCode = ActiveCode;

	bool bRightData = ReqData.IsValid(ResponseResult);
	if (!bRightData)
	{
		CallOnFail(AsyncID, false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult));
		return ;
	}
	//TODO 统一加密方式
	ReqData.ManagerPassword = FMD5::HashAnsiString(*ManagerPassword);

	//2.获取本地配置的远端服务器信息
	if (!UXGLoginClientSettings::GetXGLoginServerSettings()->LoadXGLoginServerIPAndPort(ServerIP, ServerPort))
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		CallOnFail(AsyncID, false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult));
		return ;
	}

	//3.反序列化请求数据

	FString ReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(ReqData, ReqDataStr);

	//4.发出请求
	SendHttp(EXGLoginRequestType::CheckOneStatusReq, ReqDataStr);
	
}

void UXGLoginClientCheckOneStatusACAA::SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	FXGLoginServerRequest LoginServerRequest;
	LoginServerRequest.RequestType = InRequestType;
	LoginServerRequest.Data = InRequestDataStr;

	FString RequestBody;
	FJsonObjectConverter::UStructToJsonObjectString(LoginServerRequest, RequestBody);

	Request->OnProcessRequestComplete().BindUObject(this, &UXGLoginClientCheckOneStatusACAA::OnHttpRespReceived, LoginServerRequest.RequestType);

	FString URL = FString::Printf(TEXT("http://%s:%s/Login"), *ServerIP, *ServerPort);
	Request->SetURL(URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("XGLoginServerToken", TCHAR_TO_ANSI(*UXGLoginClientSettings::GetXGLoginServerSettings()->GenerateToken()));

	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();


}

void UXGLoginClientCheckOneStatusACAA::OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType )
{
	UE_LOG(LogXGLoginClient, Display, TEXT("[%s],AsyncID:[%s],Receive CheckOneStatus HttpResonpse"), *FString(__FUNCTION__), *AsyncID.ToString());

	EXGLoginServerResult ServerResult = EXGLoginServerResult::NetError;

	FString ResponseJson = TEXT("");

	if (!HttpResponse.IsValid())
	{
		ResponseJson = TEXT("HttpResponse is Null!Please check your URL is right?");

		UE_LOG(LogXGLoginClient, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, TEXT("Http Failed,Message:") + ResponseJson);

		RealeaseResources();

		return;
	}

	ResponseJson = HttpResponse->GetContentAsString();


	if (bSucceeded && HttpRequest->GetStatus() == EHttpRequestStatus::Succeeded && HttpResponse->GetResponseCode() == 200)
	{
		FXGLoginServerResponse  XGLoginServerResponse;

		if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseJson, &XGLoginServerResponse))
		{
			if (XGLoginServerResponse.ResultType == EXGLoginServerResult::Succeeded)
			{

				FXGCheckOneStatusRespData RespData;

				if (FJsonObjectConverter::JsonObjectStringToUStruct(XGLoginServerResponse.Data, &RespData))
				{

					ServerResult = EXGLoginServerResult::Succeeded;

					CallOnSuccess(AsyncID, true, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult), RespData.ActiveCodeInfo);

					
				}
				else
				{

					ServerResult = EXGLoginServerResult::ParseServerResponseDataFailed;
				}
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


	if (ServerResult!= EXGLoginServerResult::Succeeded)
	{
		FString ErrorMessage = FString::Printf(TEXT("ServerResultType:[%s],ResponseContent:[%s]"),
			*FXGLoginServerUtil::XGLoginServerResultToString(ServerResult),
			*ResponseJson);

		UE_LOG(LogXGLoginClient, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, *ErrorMessage);
	}


	RealeaseResources();

}

void UXGLoginClientCheckOneStatusACAA::CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage,  FXGActiveCodeInfo InCodeInfo)
{
	FXGLoginClientCheckOneStatusACDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, InCodeInfo);


		});
}

void UXGLoginClientCheckOneStatusACAA::CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage)
{
	FXGLoginClientCheckOneStatusACDelegate TempDelegate = OnFail;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, FXGActiveCodeInfo());


		});
}

void UXGLoginClientCheckOneStatusACAA::RealeaseResources()
{

	ManagerName = TEXT("");

	ManagerPassword = TEXT("");

	ActiveCode =TEXT("");

	Then.Clear();
	
	OnSuccess.Clear();

	OnFail.Clear();

	SetReadyToDestroy();
}
