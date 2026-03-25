#include "AI/SmartObject/Tasks/BTTask_ClaimSmartObject.h"

#include "AI/Controllers/SmartObjectAIController.h"

UBTTask_ClaimSmartObject::UBTTask_ClaimSmartObject()
{
	NodeName = TEXT("Claim SmartObject");
}

EBTNodeResult::Type UBTTask_ClaimSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASmartObjectAIController* AIController = Cast<ASmartObjectAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	return AIController->ClaimSmartObject() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
