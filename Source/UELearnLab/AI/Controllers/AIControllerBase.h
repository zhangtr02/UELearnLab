#pragma once

#include "CoreMinimal.h"
#include "AI/Common/AIConstants.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

class AAICharacterBase;
class UEQSQueryComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class UELEARNLAB_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	AActor* GetCurrentTargetActor() const { return CurrentTargetActor.Get(); }
	float GetDistanceToTarget(float InvalidDistance = UELearnLabAI::InvalidTargetDistance) const;
	AAICharacterBase* GetControlledAICharacter() const;
	UEQSQueryComponent* GetEQSQueryComponent() const { return EQSQueryComponent; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void InitializeSightConfig();
	void SetCurrentTargetActor(AActor* NewTargetActor);
	virtual void ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus);

	virtual void OnTargetActorUpdated(AActor* NewTargetActor);
	virtual bool IsValidTargetActor(AActor* Actor) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Target")
	TObjectPtr<AActor> CurrentTargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|EQS")
	TObjectPtr<UEQSQueryComponent> EQSQueryComponent;
};
