


#include "AI/BT/Decorators/BTDecorator_IsInAttackRange.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("Is In Attack Range");

	DistanceToTargetKey.AddFloatFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTDecorator_IsInAttackRange, DistanceToTargetKey)
	);
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}

	const float Distance = BlackboardComp->GetValueAsFloat(DistanceToTargetKey.SelectedKeyName);
	return Distance <= AttackRange;
}
