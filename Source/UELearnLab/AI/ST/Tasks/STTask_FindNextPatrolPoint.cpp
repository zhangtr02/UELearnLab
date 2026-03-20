#include "STTask_FindNextPatrolPoint.h"

#include "StateTreeExecutionContext.h"
#include "AI/Characters/AICharacterBase.h"
#include "AI/Controllers/STAIController.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Pawn.h"

EStateTreeRunStatus FSTTask_FindNextPatrolPoint::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

	UObject* OwnerObject = Context.GetOwner();
	const ASTAIController* OwnerController = Cast<ASTAIController>(OwnerObject);
	if (!OwnerController)
	{
		return EStateTreeRunStatus::Failed;
	}

	APawn* OwnerPawn = OwnerController->GetPawn();
	if (!OwnerPawn)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	AAICharacterBase* AICharacter = Cast<AAICharacterBase>(OwnerPawn);

	const int32 NumPatrolPoints = AICharacter->PatrolPoints.Num();
	if (NumPatrolPoints <= 0)
	{
		return EStateTreeRunStatus::Failed;
	}

	if (!AICharacter->PatrolPoints.IsValidIndex(AICharacter->CurrentPatrolIndex))
	{
		AICharacter->CurrentPatrolIndex = 0;
	}

	const AActor* PatrolPoint = AICharacter->PatrolPoints[AICharacter->CurrentPatrolIndex];
	if (!PatrolPoint)
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.PatrolLocation = PatrolPoint->GetActorLocation();

	AICharacter->CurrentPatrolIndex = (AICharacter->CurrentPatrolIndex + 1) % NumPatrolPoints;

	return EStateTreeRunStatus::Succeeded;
}