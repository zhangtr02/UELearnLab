#pragma once

#include "CoreMinimal.h"
#include "AI/Common/AIConstants.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdatePerceptionState.generated.h"

UCLASS()
class UELEARNLAB_API UBTService_UpdatePerceptionState : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdatePerceptionState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DistanceToTargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LastKnownTargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector CanSeeTargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HasHeardTargetKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float NoTargetDistance = UELearnLabAI::InvalidTargetDistance;
};
