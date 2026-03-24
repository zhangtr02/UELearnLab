#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/BTAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "PerceptionAIController.generated.h"

class UAISenseConfig_Hearing;

USTRUCT(BlueprintType)
struct UELEARNLAB_API FPerceptionTargetInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	FVector LastKnownLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	bool bHasLastKnownLocation = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	bool bCanSeeTarget = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	bool bHasHeardTarget = false;

	void Reset()
	{
		LastKnownLocation = FVector::ZeroVector;
		bHasLastKnownLocation = false;
		bCanSeeTarget = false;
		bHasHeardTarget = false;
	}
};

UCLASS()
class UELEARNLAB_API APerceptionAIController : public ABTAIController
{
	GENERATED_BODY()

public:
	APerceptionAIController();

	const FPerceptionTargetInfo& GetTargetInfo() const { return TargetInfo; }
	FVector GetLastKnownTargetLocation(const FVector& FallbackLocation = FVector::ZeroVector) const;
	bool CanCurrentlySeeTarget() const { return TargetInfo.bCanSeeTarget && GetCurrentTargetActor() != nullptr; }
	bool HasHeardCurrentTarget() const { return TargetInfo.bHasHeardTarget && GetCurrentTargetActor() != nullptr; }

protected:
	void InitializeHearingConfig();
	void RefreshTargetInfo(AActor* Actor);
	virtual void ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	FPerceptionTargetInfo TargetInfo;
};
