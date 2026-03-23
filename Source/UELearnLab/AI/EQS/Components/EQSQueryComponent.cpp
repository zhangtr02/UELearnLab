#include "AI/EQS/Components/EQSQueryComponent.h"

#include "AI/Controllers/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UEQSQueryComponent::UEQSQueryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEQSQueryComponent::RunSingleLocationQuery(
	AAIControllerBase* OwnerController,
	UEnvQuery* QueryTemplate,
	const FName BlackboardLocationKeyName)
{
	if (ActiveQuery || !OwnerController || !OwnerController->GetPawn() || !OwnerController->GetCurrentTargetActor())
	{
		return;
	}

	if (!QueryTemplate || BlackboardLocationKeyName.IsNone())
	{
		return;
	}

	CachedController = OwnerController;
	CachedLocationKeyName = BlackboardLocationKeyName;

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
		OwnerController,
		QueryTemplate,
		OwnerController,
		EEnvQueryRunMode::SingleResult,
		nullptr
	);

	if (!QueryInstance)
	{
		ResetActiveQuery();
		return;
	}

	ActiveQuery = QueryInstance;
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &UEQSQueryComponent::HandleQueryFinished);
}

void UEQSQueryComponent::HandleQueryFinished(
	UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	const EEnvQueryStatus::Type QueryStatus)
{
	if (QueryInstance != ActiveQuery)
	{
		return;
	}

	const TWeakObjectPtr<AAIControllerBase> OwnerController = CachedController;
	const FName LocationKeyName = CachedLocationKeyName;

	ResetActiveQuery();

	if (QueryStatus != EEnvQueryStatus::Success || !OwnerController.IsValid() || !OwnerController->GetCurrentTargetActor())
	{
		return;
	}

	TArray<FVector> ResultLocations;
	QueryInstance->GetQueryResultsAsLocations(ResultLocations);

	if (ResultLocations.IsEmpty())
	{
		if (UBlackboardComponent* BlackboardComp = OwnerController->GetBlackboardComponent())
		{
			BlackboardComp->ClearValue(LocationKeyName);
		}

		return;
	}

	const FVector BestLocation = ResultLocations[0];

	if (UBlackboardComponent* BlackboardComp = OwnerController->GetBlackboardComponent())
	{
		BlackboardComp->SetValueAsVector(LocationKeyName, BestLocation);
	}
}

void UEQSQueryComponent::ResetActiveQuery()
{
	ActiveQuery = nullptr;
	CachedController.Reset();
	CachedLocationKeyName = NAME_None;
}
