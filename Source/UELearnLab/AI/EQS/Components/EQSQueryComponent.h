#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EQSQueryComponent.generated.h"

class AAIControllerBase;
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;

UCLASS(ClassGroup = (AI), meta = (BlueprintSpawnableComponent))
class UELEARNLAB_API UEQSQueryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEQSQueryComponent();

	void RunSingleLocationQuery(
		AAIControllerBase* OwnerController,
		UEnvQuery* QueryTemplate,
		FName BlackboardLocationKeyName
	);

protected:
	UFUNCTION()
	void HandleQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	void ResetActiveQuery();

protected:
	UPROPERTY(Transient)
	TObjectPtr<UEnvQueryInstanceBlueprintWrapper> ActiveQuery;

	TWeakObjectPtr<AAIControllerBase> CachedController;
	FName CachedLocationKeyName = NAME_None;
};
