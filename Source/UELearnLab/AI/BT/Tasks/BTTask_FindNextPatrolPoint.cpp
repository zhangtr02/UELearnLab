
#include "AI/BT/Tasks/BTTask_FindNextPatrolPoint.h"

#include "AI/Characters/AICharacterBase.h"
#include "AI/Controllers/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNextPatrolPoint::UBTTask_FindNextPatrolPoint()
{
	NodeName = TEXT("Find Next Patrol Point");
	PatrolLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextPatrolPoint, PatrolLocationKey));
}

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AAICharacterBase* AICharacter = AIController->GetControlledAICharacter();
	if (!AICharacter)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector PatrolLocation = FVector::ZeroVector;
	if (!AICharacter->TryGetNextPatrolLocation(PatrolLocation))
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsVector(PatrolLocationKey.SelectedKeyName, PatrolLocation);
	return EBTNodeResult::Succeeded;
}
