#include "AI/SmartObject/Services/BTService_UpdateSmartObjectState.h"

#include "AI/Controllers/SmartObjectAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateSmartObjectState::UBTService_UpdateSmartObjectState()
{
	NodeName = TEXT("Update SmartObject State");
	Interval = 0.2f;
	RandomDeviation = 0.0f;

	SmartObjectLocationKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateSmartObjectState, SmartObjectLocationKey)
	);

	HasAvailableSmartObjectKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateSmartObjectState, HasAvailableSmartObjectKey)
	);

	HasClaimedSmartObjectKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateSmartObjectState, HasClaimedSmartObjectKey)
	);
}

void UBTService_UpdateSmartObjectState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASmartObjectAIController* AIController = Cast<ASmartObjectAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	AIController->UpdateSmartObjectCandidate(SearchRadius);

	const bool bHasAvailableSmartObject = AIController->HasAvailableSmartObject();
	const bool bHasClaimedSmartObject = AIController->HasClaimedSmartObject();

	if (bHasAvailableSmartObject)
	{
		BlackboardComp->SetValueAsVector(
			SmartObjectLocationKey.SelectedKeyName,
			AIController->GetSmartObjectLocation()
		);
	}
	else
	{
		BlackboardComp->ClearValue(SmartObjectLocationKey.SelectedKeyName);
	}

	BlackboardComp->SetValueAsBool(HasAvailableSmartObjectKey.SelectedKeyName, bHasAvailableSmartObject);
	BlackboardComp->SetValueAsBool(HasClaimedSmartObjectKey.SelectedKeyName, bHasClaimedSmartObject);
}
