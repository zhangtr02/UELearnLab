#include "AI/ST/Evaluators/STEvaluator_UpdateTargetInfo.h"

#include "AI/Controllers/AIControllerBase.h"
#include "StateTreeExecutionContext.h"

const UStruct* FSTEvaluator_UpdateTargetInfo::GetInstanceDataType() const
{
	return FInstanceDataType::StaticStruct();
}

void FSTEvaluator_UpdateTargetInfo::TreeStart(FStateTreeExecutionContext& Context) const
{
	Update(Context);
}

void FSTEvaluator_UpdateTargetInfo::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	Update(Context);
}

void FSTEvaluator_UpdateTargetInfo::Update(FStateTreeExecutionContext& Context) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

	const AAIControllerBase* OwnerController = Cast<AAIControllerBase>(Context.GetOwner());
	if (!OwnerController)
	{
		InstanceData.TargetActor = nullptr;
		InstanceData.DistanceToTarget = UELearnLabAI::InvalidTargetDistance;
		return;
	}

	InstanceData.TargetActor = OwnerController->GetCurrentTargetActor();
	InstanceData.DistanceToTarget = OwnerController->GetDistanceToTarget(UELearnLabAI::InvalidTargetDistance);
}
