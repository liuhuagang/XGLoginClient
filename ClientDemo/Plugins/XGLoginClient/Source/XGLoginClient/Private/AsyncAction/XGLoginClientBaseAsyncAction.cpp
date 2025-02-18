
// Copyright 2025 Huagang Liu. All Rights Reserved.

#include "XGLoginClientBaseAsyncAction.h"

#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"

UXGLoginClientBaseAsyncAction::UXGLoginClientBaseAsyncAction(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	AsyncID(FGuid::NewGuid())
{
}

void UXGLoginClientBaseAsyncAction::Activate()
{
	Super::Activate();

	AsyncTask(ENamedThreads::GameThread, [this]() {

		this->Activate_Internal();

		});
}

void UXGLoginClientBaseAsyncAction::Activate_Internal()
{

}
