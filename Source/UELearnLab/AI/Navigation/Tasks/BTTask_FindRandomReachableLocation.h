#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomReachableLocation.generated.h"

UCLASS()
class UELEARNLAB_API UBTTask_FindRandomReachableLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomReachableLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RandomLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector OriginActorKey;

	UPROPERTY(EditAnywhere, Category = "Navigation", meta = (ClampMin = "0.0"))
	float SearchRadius = 1000.0f;
};
