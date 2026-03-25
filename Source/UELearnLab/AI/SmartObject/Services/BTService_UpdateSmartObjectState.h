#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateSmartObjectState.generated.h"

UCLASS()
class UELEARNLAB_API UBTService_UpdateSmartObjectState : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateSmartObjectState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SmartObjectLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HasAvailableSmartObjectKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HasClaimedSmartObjectKey;

	UPROPERTY(EditAnywhere, Category = "SmartObject", meta = (ClampMin = "0.0"))
	float SearchRadius = 1200.0f;
};
