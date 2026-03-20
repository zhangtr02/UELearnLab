#include "STTask_Attack.h"
#include "StateTreeExecutionContext.h"
#include "Engine/Engine.h"

EStateTreeRunStatus FSTTask_Attack::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		InstanceData.DebugMessageTime,
		FColor::Red,
		TEXT("Attack!"),
		true,
		FVector2D(3.0f, 3.0f)
		);

	return EStateTreeRunStatus::Succeeded;
}