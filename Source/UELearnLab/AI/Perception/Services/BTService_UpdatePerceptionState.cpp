#include "AI/Perception/Services/BTService_UpdatePerceptionState.h"

#include "AI/Controllers/PerceptionAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePerceptionState::UBTService_UpdatePerceptionState()
{
	NodeName = TEXT("Update Perception State");
	Interval = 0.2f;
	RandomDeviation = 0.0f;

	TargetActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdatePerceptionState, TargetActorKey),
		AActor::StaticClass()
	);

	LastKnownTargetLocationKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdatePerceptionState, LastKnownTargetLocationKey)
	);

	CanSeeTargetKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdatePerceptionState, CanSeeTargetKey)
	);

	HasHeardTargetKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdatePerceptionState, HasHeardTargetKey)
	);
}

void UBTService_UpdatePerceptionState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APerceptionAIController* AIController = Cast<APerceptionAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	const FPerceptionTargetInfo& TargetInfo = AIController->GetTargetInfo();

	if (AActor* TargetActor = AIController->GetCurrentTargetActor())
	{
		BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, TargetActor);
		BlackboardComp->SetValueAsVector(
			LastKnownTargetLocationKey.SelectedKeyName,
			AIController->GetLastKnownTargetLocation(TargetActor->GetActorLocation())
		);
	}
	else
	{
		BlackboardComp->ClearValue(TargetActorKey.SelectedKeyName);
		BlackboardComp->SetValueAsVector(
			LastKnownTargetLocationKey.SelectedKeyName,
			AIController->GetLastKnownTargetLocation(FVector::ZeroVector)
		);
	}
	
	BlackboardComp->SetValueAsBool(CanSeeTargetKey.SelectedKeyName, TargetInfo.bCanSeeTarget);
	BlackboardComp->SetValueAsBool(HasHeardTargetKey.SelectedKeyName, TargetInfo.bHasHeardTarget);
}
