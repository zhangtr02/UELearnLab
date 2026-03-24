#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/BTAIController.h"
#include "AI/Team/Types/TeamTypes.h"
#include "TeamAIController.generated.h"

UCLASS()
class UELEARNLAB_API ATeamAIController : public ABTAIController
{
	GENERATED_BODY()

public:
	ATeamAIController();

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	ETeamLabId GetTeamId() const { return TeamId; }
	ETeamLabId GetActorTeamId(const AActor* Actor) const;
	bool IsHostileActor(const AActor* Actor) const;

protected:
	virtual bool IsValidTargetActor(AActor* Actor) const override;
	virtual void ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Team")
	ETeamLabId TeamId = ETeamLabId::Red;
};
