#include "AI/ST/Tasks/STTask_FindNextPatrolPoint.h"

#include "AI/Characters/AICharacterBase.h"
#include "AI/Controllers/AIControllerBase.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTTask_FindNextPatrolPoint::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

	const AAIControllerBase* OwnerController = Cast<AAIControllerBase>(Context.GetOwner());
	if (!OwnerController)
	{
		return EStateTreeRunStatus::Failed;
	}

	AAICharacterBase* AICharacter = OwnerController->GetControlledAICharacter();
	if (!AICharacter)
	{
		return EStateTreeRunStatus::Failed;
	}

	return AICharacter->TryGetNextPatrolLocation(InstanceData.PatrolLocation)
		? EStateTreeRunStatus::Succeeded
		: EStateTreeRunStatus::Failed;
}
