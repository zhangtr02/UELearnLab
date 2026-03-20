


#include "AI/BT/Services/BTService_UpdateTargetInfo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateTargetInfo::UBTService_UpdateTargetInfo()
{
	NodeName = TEXT("Update Target Info");

	Interval = 0.2f;
	RandomDeviation = 0.0f;

	TargetActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTargetInfo, TargetActorKey),
		AActor::StaticClass()
	);

	DistanceToTargetKey.AddFloatFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTargetInfo, DistanceToTargetKey)
	);
}

void UBTService_UpdateTargetInfo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	const APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	UObject* TargetObject = BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName);
	const AActor* TargetActor = Cast<AActor>(TargetObject);

	if (!TargetActor)
	{
		BlackboardComp->SetValueAsFloat(DistanceToTargetKey.SelectedKeyName, NoTargetDistance);
		return;
	}

	const float Distance = FVector::Dist(
		ControlledPawn->GetActorLocation(),
		TargetActor->GetActorLocation()
	);

	BlackboardComp->SetValueAsFloat(DistanceToTargetKey.SelectedKeyName, Distance);
}
