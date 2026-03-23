#include "AI/ST/Tasks/STTask_Attack.h"

#include "AI/Common/AIDebugHelper.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTTask_Attack::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);
	UELearnLabAI::ShowAttackDebugMessage(InstanceData.DebugMessageTime);
	return EStateTreeRunStatus::Succeeded;
}
