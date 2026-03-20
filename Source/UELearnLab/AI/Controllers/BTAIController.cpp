#include "AI/Controllers/BTAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABTAIController::ABTAIController()
{
}

void ABTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void ABTAIController::OnTargetActorUpdated(AActor* NewTargetActor)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	if (NewTargetActor)
	{
		BlackboardComp->SetValueAsObject(TargetActorKeyName, NewTargetActor);
	}
	else
	{
		BlackboardComp->ClearValue(TargetActorKeyName);
	}
}