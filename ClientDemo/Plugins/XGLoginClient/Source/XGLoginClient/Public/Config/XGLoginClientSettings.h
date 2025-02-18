// Copyright (c) XiaoGang.2023.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DeveloperSettings.h"
#include "Interfaces/IPluginManager.h"
#include "XGLoginClientSettings.generated.h"


UCLASS(Config = DataBase, defaultconfig)
class XGLOGINCLIENT_API UXGLoginClientSettings : public UDeveloperSettings
{
	GENERATED_BODY()




public:

	UXGLoginClientSettings()
	{


		// 获取插件管理器
		IPluginManager& PluginManager = IPluginManager::Get();

		// 获取插件描述符
		TSharedPtr<IPlugin> PluginPtr = PluginManager.FindPlugin(TEXT("XGLoginClient"));

		if (PluginPtr.IsValid())
		{
			FPluginDescriptor PluginDescriptor = PluginPtr->GetDescriptor();
			ClientVersion = PluginDescriptor.VersionName;
		}

	}

	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("XGPlugins"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("XGLoginServerSettings"); }

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XGLoginClient")
	FString ClientVersion=TEXT("0.0.0");

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient")
	FString ServerIP=TEXT("127.0.0.1");

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient")
	FString ServerPort=TEXT("8036");

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "XGLoginClient")
	int32 HashNum=10;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite,Category = "XGLoginClient")
	FString Token=TEXT("XG");



public:

	UFUNCTION(BlueprintCallable, Category = "XGLoginClient")
	static UXGLoginClientSettings* GetXGLoginServerSettings();

	bool LoadXGLoginServerIPAndPort(FString &OutServerIP, FString &OutServerPort);

	FString GenerateToken();


};


