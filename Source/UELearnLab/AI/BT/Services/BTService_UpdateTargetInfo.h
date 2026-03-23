

#pragma once

#include "CoreMinimal.h"
#include "AI/Common/AIConstants.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateTargetInfo.generated.h"


UCLASS()
class UELEARNLAB_API UBTService_UpdateTargetInfo : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateTargetInfo();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DistanceToTargetKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float NoTargetDistance = UELearnLabAI::InvalidTargetDistance;
};
