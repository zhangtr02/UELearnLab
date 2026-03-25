#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ReleaseSmartObject.generated.h"

UCLASS()
class UELEARNLAB_API UBTTask_ReleaseSmartObject : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ReleaseSmartObject();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
