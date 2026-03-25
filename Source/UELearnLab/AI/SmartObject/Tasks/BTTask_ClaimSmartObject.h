#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClaimSmartObject.generated.h"

UCLASS()
class UELEARNLAB_API UBTTask_ClaimSmartObject : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ClaimSmartObject();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
