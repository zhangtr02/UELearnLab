#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateMoveToLocationFromEQS.generated.h"

class UEnvQuery;

UCLASS()
class UELEARNLAB_API UBTService_UpdateMoveToLocationFromEQS : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateMoveToLocationFromEQS();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "EQS")
	TObjectPtr<UEnvQuery> QueryTemplate;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector MoveToLocationKey;
};
