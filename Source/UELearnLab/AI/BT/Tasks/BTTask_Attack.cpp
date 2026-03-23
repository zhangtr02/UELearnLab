


#include "AI/BT/Tasks/BTTask_Attack.h"

#include "AI/Common/AIDebugHelper.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UELearnLabAI::ShowAttackDebugMessage(DebugMessageTime);
	return EBTNodeResult::Succeeded;
}
