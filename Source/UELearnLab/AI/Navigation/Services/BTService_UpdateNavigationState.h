#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateNavigationState.generated.h"

class UNavigationPath;

UCLASS()
class UELEARNLAB_API UBTService_UpdateNavigationState : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateNavigationState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float CalculatePathLength(const UNavigationPath* NavigationPath) const;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ReachableTargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector CanReachTargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector PathLengthKey;

	UPROPERTY(EditAnywhere, Category = "Navigation")
	float InvalidPathLength = -1.0f;
};
