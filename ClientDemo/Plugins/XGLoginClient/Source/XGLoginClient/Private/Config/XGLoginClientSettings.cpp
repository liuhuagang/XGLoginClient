// Copyright 2025 Huagang Liu. All Rights Reserved.

#include "XGLoginClientSettings.h"
#include "Log/LogXGLoginClient.h"

UXGLoginClientSettings* UXGLoginClientSettings::GetXGLoginServerSettings()
{
	UXGLoginClientSettings* Settings = GetMutableDefault<UXGLoginClientSettings>();
	return Settings;

}

bool UXGLoginClientSettings::LoadXGLoginServerIPAndPort(FString& OutServerIP, FString& OutServerPort)
{
	OutServerIP = UXGLoginClientSettings::GetXGLoginServerSettings()->ServerIP;
	OutServerPort = UXGLoginClientSettings::GetXGLoginServerSettings()->ServerPort;

	bool bServerIP = true && !OutServerIP.IsEmpty();
	bool bServerPort = OutServerPort.IsNumeric();

	if (bServerIP && bServerPort)
	{
		UE_LOG(LogXGLoginClient, Log, TEXT("[%s],ServerIP: %s"), *FString(__FUNCTION__), *OutServerIP);
		UE_LOG(LogXGLoginClient, Log, TEXT("[%s],ServerPort: %s"), *FString(__FUNCTION__), *OutServerPort);
		return true;
	}

	return false;

}

FString UXGLoginClientSettings::GenerateToken()
{
	FString ClientToken = Token;

	for (int32 Index = 0; Index < HashNum; Index++)
	{
		ClientToken = FMD5::HashAnsiString(*ClientToken);

	}

	return ClientToken;
}
