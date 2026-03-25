#include "AI/SmartObject/Tasks/BTTask_ReleaseSmartObject.h"

#include "AI/Controllers/SmartObjectAIController.h"

UBTTask_ReleaseSmartObject::UBTTask_ReleaseSmartObject()
{
	NodeName = TEXT("Release SmartObject");
}

EBTNodeResult::Type UBTTask_ReleaseSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASmartObjectAIController* AIController = Cast<ASmartObjectAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AIController->ReleaseSmartObject();
	return EBTNodeResult::Succeeded;
}
