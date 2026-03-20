


#include "AI/BT/Tasks/BTTask_Attack.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		1.5f,
		FColor::Red,
		TEXT("Attack!"),
		true,
		FVector2D(3.0f, 3.0f)
		);
	
	return EBTNodeResult::Succeeded;
}
