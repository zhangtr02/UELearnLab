#include "AI/Navigation/Services/BTService_UpdateNavigationState.h"

#include "AI/Controllers/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

UBTService_UpdateNavigationState::UBTService_UpdateNavigationState()
{
	NodeName = TEXT("Update Navigation State");
	Interval = 0.2f;
	RandomDeviation = 0.0f;

	TargetActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateNavigationState, TargetActorKey),
		AActor::StaticClass()
	);

	ReachableTargetLocationKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateNavigationState, ReachableTargetLocationKey)
	);

	CanReachTargetKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateNavigationState, CanReachTargetKey)
	);

	PathLengthKey.AddFloatFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateNavigationState, PathLengthKey)
	);
}

void UBTService_UpdateNavigationState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!ControlledPawn || !BlackboardComp)
	{
		return;
	}

	AActor* TargetActor = nullptr;
	if (!TargetActorKey.SelectedKeyName.IsNone())
	{
		TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	}

	if (!TargetActor)
	{
		TargetActor = AIController->GetCurrentTargetActor();
	}

	if (!TargetActor)
	{
		BlackboardComp->ClearValue(ReachableTargetLocationKey.SelectedKeyName);
		BlackboardComp->SetValueAsBool(CanReachTargetKey.SelectedKeyName, false);
		BlackboardComp->SetValueAsFloat(PathLengthKey.SelectedKeyName, InvalidPathLength);
		return;
	}

	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(
		AIController,
		ControlledPawn->GetActorLocation(),
		TargetActor
	);

	if (!NavigationPath || NavigationPath->PathPoints.IsEmpty())
	{
		BlackboardComp->ClearValue(ReachableTargetLocationKey.SelectedKeyName);
		BlackboardComp->SetValueAsBool(CanReachTargetKey.SelectedKeyName, false);
		BlackboardComp->SetValueAsFloat(PathLengthKey.SelectedKeyName, InvalidPathLength);
		return;
	}

	BlackboardComp->SetValueAsVector(
		ReachableTargetLocationKey.SelectedKeyName,
		NavigationPath->PathPoints.Last()
	);
	BlackboardComp->SetValueAsBool(
		CanReachTargetKey.SelectedKeyName,
		NavigationPath->IsValid() && !NavigationPath->IsPartial()
	);
	BlackboardComp->SetValueAsFloat(
		PathLengthKey.SelectedKeyName,
		CalculatePathLength(NavigationPath)
	);
}

float UBTService_UpdateNavigationState::CalculatePathLength(const UNavigationPath* NavigationPath) const
{
	if (!NavigationPath || NavigationPath->PathPoints.Num() < 2)
	{
		return 0.0f;
	}

	float PathLength = 0.0f;
	for (int32 PathIndex = 1; PathIndex < NavigationPath->PathPoints.Num(); ++PathIndex)
	{
		PathLength += FVector::Dist(
			NavigationPath->PathPoints[PathIndex - 1],
			NavigationPath->PathPoints[PathIndex]
		);
	}

	return PathLength;
}
