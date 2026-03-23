#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/AIControllerBase.h"
#include "BTAIController.generated.h"

class UBehaviorTree;

UCLASS()
class UELEARNLAB_API ABTAIController : public AAIControllerBase
{
	GENERATED_BODY()

public:
	ABTAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnTargetActorUpdated(AActor* NewTargetActor) override;

	void SyncTargetActorToBlackboard(AActor* NewTargetActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|BT")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|BT")
	FName TargetActorKeyName = TEXT("TargetActor");
};
