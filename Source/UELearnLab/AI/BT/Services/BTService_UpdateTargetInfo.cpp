


#include "AI/BT/Services/BTService_UpdateTargetInfo.h"

#include "AI/Controllers/AIControllerBase.h"
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

	const AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	if (AActor* TargetActor = AIController->GetCurrentTargetActor())
	{
		BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, TargetActor);
	}
	else
	{
		BlackboardComp->ClearValue(TargetActorKey.SelectedKeyName);
	}

	BlackboardComp->SetValueAsFloat(
		DistanceToTargetKey.SelectedKeyName,
		AIController->GetDistanceToTarget(NoTargetDistance)
	);
}
