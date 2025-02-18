// Copyright 2024 Huagang Liu. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "XGLoginServerUtil.h"
#include "XGLoginServerRequestType.h"

#include "XGLoginServerCVReqType.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FXGCheckVersionReqData :public FXGLoginServerDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGLogin|RequestType")
	FString ClientVersion = TEXT("1.0.0");

	virtual	bool IsValid(EXGLoginServerResult& OutRequestDataValidity) const override
	{
		if (ClientVersion.IsEmpty())
		{
			OutRequestDataValidity = EXGLoginServerResult::IllVersion;
			return false;
		}
		OutRequestDataValidity = EXGLoginServerResult::Succeeded;
		return true;
	}

};
