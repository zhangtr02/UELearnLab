#include "AI/EQS/Contexts/EnvQueryContext_CurrentTarget.h"

#include "AI/Controllers/AIControllerBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "GameFramework/Pawn.h"

void UEnvQueryContext_CurrentTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const UObject* QueryOwner = QueryInstance.Owner.Get();
	const AAIControllerBase* AIController = Cast<AAIControllerBase>(QueryOwner);

	if (!AIController)
	{
		const APawn* Pawn = Cast<APawn>(QueryOwner);
		if (Pawn)
		{
			AIController = Cast<AAIControllerBase>(Pawn->GetController());
		}
	}

	if (!AIController)
	{
		return;
	}

	AActor* CurrentTarget = AIController->GetCurrentTargetActor();
	if (!CurrentTarget)
	{
		return;
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, CurrentTarget);
}
