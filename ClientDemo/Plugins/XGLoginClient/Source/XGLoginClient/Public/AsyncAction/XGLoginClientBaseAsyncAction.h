// Copyright 2025 Huagang Liu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "XGLoginClientBaseAsyncAction.generated.h"

UCLASS()
class XGLOGINCLIENT_API UXGLoginClientBaseAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	UXGLoginClientBaseAsyncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Activate() override;

protected:

	virtual void Activate_Internal();

public:

	FGuid AsyncID;
};
