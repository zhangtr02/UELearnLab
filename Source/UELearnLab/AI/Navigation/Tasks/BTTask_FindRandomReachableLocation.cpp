#include "AI/Navigation/Tasks/BTTask_FindRandomReachableLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomReachableLocation::UBTTask_FindRandomReachableLocation()
{
	NodeName = TEXT("Find Random Reachable Location");

	RandomLocationKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomReachableLocation, RandomLocationKey)
	);

	OriginActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomReachableLocation, OriginActorKey),
		AActor::StaticClass()
	);
}

EBTNodeResult::Type UBTTask_FindRandomReachableLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!ControlledPawn || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	const AActor* OriginActor = nullptr;
	if (!OriginActorKey.SelectedKeyName.IsNone())
	{
		OriginActor = Cast<AActor>(BlackboardComp->GetValueAsObject(OriginActorKey.SelectedKeyName));
	}

	const FVector OriginLocation = OriginActor ? OriginActor->GetActorLocation() : ControlledPawn->GetActorLocation();

	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ControlledPawn->GetWorld());
	if (!NavigationSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation ReachableLocation;
	if (!NavigationSystem->GetRandomReachablePointInRadius(OriginLocation, SearchRadius, ReachableLocation))
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsVector(RandomLocationKey.SelectedKeyName, ReachableLocation.Location);
	return EBTNodeResult::Succeeded;
}
