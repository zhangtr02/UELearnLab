#include "AI/Team/Services/BTService_UpdateTeamState.h"

#include "AI/Controllers/TeamAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateTeamState::UBTService_UpdateTeamState()
{
	NodeName = TEXT("Update Team State");
	Interval = 0.2f;
	RandomDeviation = 0.0f;

	TargetActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTeamState, TargetActorKey),
		AActor::StaticClass()
	);

	SelfTeamIdKey.AddIntFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTeamState, SelfTeamIdKey)
	);

	TargetTeamIdKey.AddIntFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTeamState, TargetTeamIdKey)
	);

	IsTargetHostileKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTeamState, IsTargetHostileKey)
	);
}

void UBTService_UpdateTeamState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const ATeamAIController* AIController = Cast<ATeamAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
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

	BlackboardComp->SetValueAsInt(
		SelfTeamIdKey.SelectedKeyName,
		static_cast<int32>(AIController->GetTeamId())
	);

	if (!TargetActor)
	{
		BlackboardComp->SetValueAsInt(
			TargetTeamIdKey.SelectedKeyName,
			static_cast<int32>(ETeamLabId::Neutral)
		);
		BlackboardComp->SetValueAsBool(IsTargetHostileKey.SelectedKeyName, false);
		return;
	}

	BlackboardComp->SetValueAsInt(
		TargetTeamIdKey.SelectedKeyName,
		static_cast<int32>(AIController->GetActorTeamId(TargetActor))
	);
	BlackboardComp->SetValueAsBool(
		IsTargetHostileKey.SelectedKeyName,
		AIController->IsHostileActor(TargetActor)
	);
}
