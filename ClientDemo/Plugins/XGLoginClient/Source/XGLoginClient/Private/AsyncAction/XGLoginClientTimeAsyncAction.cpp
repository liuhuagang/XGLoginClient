// Copyright (c) XiaoGang 2024.All Rights Reserved.



#include "XGLoginClientTimeAsyncAction.h"

#include "JsonObjectConverter.h"
#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"

#include "LogXGLoginClient.h"

UXGLoginClientTimeAsyncAction::UXGLoginClientTimeAsyncAction(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

UXGLoginClientTimeAsyncAction::~UXGLoginClientTimeAsyncAction()
{
	RealeaseResources();
}



UXGLoginClientTimeAsyncAction* UXGLoginClientTimeAsyncAction::XGLoginClientTimeAsyncAction(UObject* WorldContextObject, 
EXGLoginClientTimeType InLoginClientTimeType,
FString InYourCustomLoginServerURL
)
{
	UXGLoginClientTimeAsyncAction* AsyncAction = NewObject<UXGLoginClientTimeAsyncAction>();

	AsyncAction->LoginClientTimeType = InLoginClientTimeType;
	AsyncAction->CustomLoginServerURL = InYourCustomLoginServerURL;

	AsyncAction->RegisterWithGameInstance(WorldContextObject);

	return AsyncAction;
}
void UXGLoginClientTimeAsyncAction::Activate()
{
	Super::Activate();

	AsyncTask(ENamedThreads::GameThread, [this]() {

		this->Activate_Internal();

		});

	FXGLoginClientTimeRespInfo RespInfo;

	Then.Broadcast(AsyncID, false, TEXT("XGLoginClientTimeAsyncAction is just started,please wait to be finished!"), RespInfo);
}

void UXGLoginClientTimeAsyncAction::Activate_Internal()
{
	UE_LOG(LogXGLoginClient, Display, TEXT("[%s],AsyncID:[%s],Begin to execute XGLoginClientTimeAsyncAction"), *FString(__FUNCTION__), *(AsyncID.ToString()));

	FString TimeServerURL = TEXT("");

	switch (LoginClientTimeType)
	{
	case EXGLoginClientTimeType::TaoBao:
		TimeServerURL = TEXT("https://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp");
		break;

	case EXGLoginClientTimeType::XGLoginServer:

		TimeServerURL = TEXT("http://47.108.203.10:8036/NetTime");
		break;
	case EXGLoginClientTimeType::CustomServer:

		TimeServerURL = CustomLoginServerURL;
		break;

	case EXGLoginClientTimeType::MaxNum:
		break;
	default:
		break;
	}


	SendHttp(TimeServerURL,TEXT(""));


}
void UXGLoginClientTimeAsyncAction::SendHttp(const FString& InServerURL, const FString& InContentString)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UXGLoginClientTimeAsyncAction::OnHttpRespReceived);

	Request->SetURL(InServerURL);

	Request->SetVerb("Post");

	Request->SetHeader("Content-Type", "application/json");

	Request->SetContentAsString(InContentString);

	Request->ProcessRequest();

}

void UXGLoginClientTimeAsyncAction::OnHttpRespReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	UE_LOG(LogXGLoginClient, Display, TEXT("[%s],AsyncID:[%s],Receive XGLoginClientTimeAsyncAction HttpResonpse"), *FString(__FUNCTION__), *(AsyncID.ToString()));

	FXGLoginClientTimeRespInfo RespInfo;

	if (bSucceeded && HttpRequest->GetStatus() == EHttpRequestStatus::Succeeded && HttpResponse->GetResponseCode() == 200)
	{
		FString ResponseJson = HttpResponse->GetContentAsString();

		UE_LOG(LogXGLoginClient, Display, TEXT("[%s]"), *ResponseJson);

		FXGLoginClientTimeRespMessage RespMessage;
		bool bParseJson = FJsonObjectConverter::JsonObjectStringToUStruct(ResponseJson, &RespMessage);

		if (bParseJson)
		{
			FString TickString =  RespMessage.data.t;

			int64 TickTime = FCString::Atoi64(*TickString)/1000;

			RespInfo.UTCDateTime=FDateTime::FromUnixTimestamp(TickTime);

			RespInfo.BeijingDateTime =FDateTime::FromUnixTimestamp(TickTime+8*60*60);

			RespInfo.RawMessage = ResponseJson;

			CallOnSuccess(AsyncID, false, TEXT("Succeed!"), RespInfo);

		}
		else
		{
			FString ErrorMessage = FString::Printf(TEXT("[%s],AsyncID:[%s],Receive XGLoginClientTimeAsyncAction HttpResonpse Parse Json Wrong!, Check Your Net or Connect The Author"), *FString(__FUNCTION__), *(AsyncID.ToString()));

			UE_LOG(LogXGLoginClient, Error, TEXT("[%s]"), *ErrorMessage);

			CallOnFail(AsyncID, false, TEXT("HTTP Failed!"), RespInfo);
		}

	}
	else
	{
		
		FString ErrorMessage = FString ::Printf(TEXT("[%s],AsyncID:[%s],Receive XGLoginClientTimeAsyncAction HttpResonpse Failed, Check Your Net"), *FString(__FUNCTION__), *(AsyncID.ToString()));

		UE_LOG(LogXGLoginClient, Error, TEXT("[%s]"), *ErrorMessage);

		CallOnFail(AsyncID, false, TEXT("HTTP Failed!"), RespInfo);




	}



	RealeaseResources();




}

void UXGLoginClientTimeAsyncAction::CallOnSuccess(FGuid InAsyncID, bool bInResult, FString InMessage, FXGLoginClientTimeRespInfo PRRespInfo)
{
	FXGLoginClientTimeDelegate TempDelegate = OnSuccess;

	AsyncTask(ENamedThreads::GameThread, [=]() {
		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, PRRespInfo);

		});

}

void UXGLoginClientTimeAsyncAction::CallOnFail(FGuid InAsyncID, bool bInResult, FString InMessage, FXGLoginClientTimeRespInfo PRRespInfo)
{
	FXGLoginClientTimeDelegate TempDelegate = OnFail;

	AsyncTask(ENamedThreads::GameThread, [=]() {
		TempDelegate.Broadcast(InAsyncID, bInResult, InMessage, PRRespInfo);

		});

}

void UXGLoginClientTimeAsyncAction::RealeaseResources()
{

	SetReadyToDestroy();
}
