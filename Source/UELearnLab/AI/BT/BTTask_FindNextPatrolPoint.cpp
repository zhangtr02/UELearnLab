


#include "AI/BT/BTTask_FindNextPatrolPoint.h"

#include "AIController.h"
#include "AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

UBTTask_FindNextPatrolPoint::UBTTask_FindNextPatrolPoint()
{
	NodeName = TEXT("Find Next Patrol Point");
	PatrolLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextPatrolPoint, PatrolLocationKey));
}

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	AAICharacter* AICharacter = Cast<AAICharacter>(ControlledPawn);
	if (!AICharacter)
	{
		return EBTNodeResult::Failed;
	}

	const int32 NumPatrolPoints = AICharacter->PatrolPoints.Num();
	if (NumPatrolPoints <= 0)
	{
		return EBTNodeResult::Failed;
	}
	
	if (!AICharacter->PatrolPoints.IsValidIndex(AICharacter->CurrentPatrolIndex))
	{
		AICharacter->CurrentPatrolIndex = 0;
	}

	const ATargetPoint* PatrolPointActor = AICharacter->PatrolPoints[AICharacter->CurrentPatrolIndex];
	if (!PatrolPointActor)
	{
		return EBTNodeResult::Failed;
	}

	const FVector PatrolLocation = PatrolPointActor->GetActorLocation();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsVector(PatrolLocationKey.SelectedKeyName, PatrolLocation);
	
	AICharacter->CurrentPatrolIndex = (AICharacter->CurrentPatrolIndex + 1) % NumPatrolPoints;

	return EBTNodeResult::Succeeded;
}
