#include "AI/EQS/Services/BTService_UpdateMoveToLocationFromEQS.h"

#include "AI/Controllers/AIControllerBase.h"
#include "AI/EQS/Components/EQSQueryComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateMoveToLocationFromEQS::UBTService_UpdateMoveToLocationFromEQS()
{
	NodeName = TEXT("Update Move To Location From EQS");
	Interval = 0.5f;
	RandomDeviation = 0.0f;

	MoveToLocationKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateMoveToLocationFromEQS, MoveToLocationKey)
	);
}

void UBTService_UpdateMoveToLocationFromEQS::TickNode(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	if (!AIController->GetCurrentTargetActor())
	{
		BlackboardComp->ClearValue(MoveToLocationKey.SelectedKeyName);
		return;
	}

	UEQSQueryComponent* EQSQueryComponent = AIController->GetEQSQueryComponent();
	if (!EQSQueryComponent || !QueryTemplate)
	{
		return;
	}

	EQSQueryComponent->RunSingleLocationQuery(
		AIController,
		QueryTemplate,
		MoveToLocationKey.SelectedKeyName
	);
}
