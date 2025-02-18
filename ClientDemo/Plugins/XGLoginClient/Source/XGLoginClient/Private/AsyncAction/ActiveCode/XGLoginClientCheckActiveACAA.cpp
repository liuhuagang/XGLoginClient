// Copyright 2025 Huagang Liu. All Rights Reserved.

#include "XGLoginClientCheckActiveACAA.h"

#include "JsonObjectConverter.h"
#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"

#include "XGLoginClientSettings.h"
#include "Log/LogXGLoginClient.h"
#include "XGLoginServerRequestType.h"
#include "XGLoginServerResponseType.h"
#include "XGLoginServerUtil.h"
#include "XGLoginClientBPLibrary.h"

UXGLoginClientCheckActiveACAA::UXGLoginClientCheckActiveACAA(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

UXGLoginClientCheckActiveACAA::~UXGLoginClientCheckActiveACAA()
{
	RealeaseResources();
}

UXGLoginClientCheckActiveACAA* UXGLoginClientCheckActiveACAA::XGLoginClientCheckActiveACAA(UObject* WorldContextObject)
{
	UXGLoginClientCheckActiveACAA* AsyncAction = NewObject<UXGLoginClientCheckActiveACAA>();

	AsyncAction->MachineID = UXGLoginClientBPLibrary::XGGetOperatingSystemId();

	AsyncAction->RegisterWithGameInstance(WorldContextObject);

	return AsyncAction;
}

void UXGLoginClientCheckActiveACAA::Activate()
{
	Super::Activate();

	Then.Broadcast(AsyncID, false,
		TEXT("XGLoginClientCheckActiveACAA is just started,please wait to be finished!"));

}

void UXGLoginClientCheckActiveACAA::Activate_Internal()
{

	EXGLoginServerResult ResponseResult;

	//1.校验数据正确与否
	FXGCheckActiveReqData ReqData;

	ReqData.MachineCode = MachineID;


	bool bRightData = ReqData.IsValid(ResponseResult);
	if (!bRightData)
	{
		CallOnFail(AsyncID, false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult));
		return;
	}

	//2.获取本地配置的远端服务器信息
	if (!UXGLoginClientSettings::GetXGLoginServerSettings()->LoadXGLoginServerIPAndPort(ServerIP, ServerPort))
	{
		ResponseResult = EXGLoginServerResult::ParseServerIpAndPortFailed;
		CallOnFail(AsyncID, false, FXGLoginServerUtil::XGLoginServerResultToString(ResponseResult));
		return;
	}

	//3.反序列化请求数据

	FString ReqDataStr = TEXT("");
	FJsonObjectConverter::UStructToJsonObjectString(ReqData, ReqDataStr);

	//4.发出请求
	SendHttp(EXGLoginRequestType::CheckActiveReq, ReqDataStr);

}

void UXGLoginClientCheckActiveACAA::SendHttp(EXGLoginRequestType InRequestType, const FString& InRequestDataStr)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	FXGLoginServerRequest LoginServerRequest;
	LoginServerRequest.RequestType = InRequestType;
	LoginServerRequest.Data = InRequestDataStr;

	FString RequestBody;
	FJsonObjectConverter::UStructToJsonObjectString(LoginServerRequest, RequestBody);

	Request->OnProcessRequestComplete().BindUObject(this, &UXGLoginClientCheckActiveACAA::OnHttpRespReceived, LoginServerRequest.RequestType);

	FString URL = FString::Printf(TEXT("http://%s:%s/Login"), *ServerIP, *ServerPort);
	Request->SetURL(URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("XGLoginServerToken", TCHAR_TO_ANSI(*UXGLoginClientSettings::GetXGLoginServerSettings()->GenerateToken()));

	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();


}

void UXGLoginClientCheckActiveACAA::OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EXGLoginRequestType RequestType)
{
	UE_LOG(LogXGLoginClient, Display, TEXT("[%s],AsyncID:[%s],Receive CheckActive HttpResonpse"), *FString(__FUNCTION__), *AsyncID.ToString());

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
				//本接口没有二级数据 不需要二级解析

				ServerResult = EXGLoginServerResult::Succeeded;

				CallOnSuccess(AsyncID, true, FXGLoginServerUtil::XGLoginServerResultToString(ServerResult));


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


	if (ServerResult != EXGLoginServerResult::Succeeded)
	{
		FString ErrorMessage = FString::Printf(TEXT("ServerResultType:[%s],ResponseContent:[%s]"),
			*FXGLoginServerUtil::XGLoginServerResultToString(ServerResult),
			*ResponseJson);

		UE_LOG(LogXGLoginClient, Warning, TEXT("[%s],Http Failed!!!!!,Message:[%s]"), *FString(__FUNCTION__), *ResponseJson);

		CallOnFail(AsyncID, false, *ErrorMessage);
	}


	RealeaseResources();

}

void UXGLoginClientCheckActiveACAA::CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage)
{
	FXGLoginClientCheckActiveACDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage);


		});
}

void UXGLoginClientCheckActiveACAA::CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage)
{
	FXGLoginClientCheckActiveACDelegate TempDelegate = OnFail;

	AsyncTask(ENamedThreads::GameThread, [=]() {

		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage);


		});
}

void UXGLoginClientCheckActiveACAA::RealeaseResources()
{


	MachineID = TEXT("");

	Then.Clear();

	OnSuccess.Clear();

	OnFail.Clear();

	SetReadyToDestroy();
}
