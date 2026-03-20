

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextPatrolPoint.generated.h"


UCLASS()
class UELEARNLAB_API UBTTask_FindNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindNextPatrolPoint();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector PatrolLocationKey;
};
