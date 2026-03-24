#include "AI/Controllers/PerceptionAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

APerceptionAIController::APerceptionAIController()
{
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	InitializeHearingConfig();
}

FVector APerceptionAIController::GetLastKnownTargetLocation(const FVector& FallbackLocation) const
{
	if (!TargetInfo.bHasLastKnownLocation)
	{
		return FallbackLocation;
	}

	return TargetInfo.LastKnownLocation;
}

void APerceptionAIController::ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus)
{
	RefreshTargetInfo(Actor);

	if (Stimulus.WasSuccessfullySensed())
	{
		TargetInfo.LastKnownLocation = Stimulus.StimulusLocation;
		TargetInfo.bHasLastKnownLocation = true;
	}
}

void APerceptionAIController::InitializeHearingConfig()
{
	if (!AIPerceptionComp || !HearingConfig)
	{
		return;
	}

	HearingConfig->HearingRange = 2000.0f;
	HearingConfig->SetMaxAge(3.0f);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComp->ConfigureSense(*HearingConfig);
}

void APerceptionAIController::RefreshTargetInfo(AActor* Actor)
{
	if (!AIPerceptionComp || !Actor)
	{
		return;
	}

	FActorPerceptionBlueprintInfo PerceptionInfo;
	AIPerceptionComp->GetActorsPerception(Actor, PerceptionInfo);

	const FAISenseID SightSenseID = UAISense::GetSenseID<UAISense_Sight>();
	const FAISenseID HearingSenseID = UAISense::GetSenseID<UAISense_Hearing>();

	bool bCanSeeTarget = false;
	bool bHasHeardTarget = false;
	FVector LastKnownLocation = TargetInfo.LastKnownLocation;

	for (const FAIStimulus& Stimulus : PerceptionInfo.LastSensedStimuli)
	{
		if (!Stimulus.IsValid())
		{
			continue;
		}

		if (Stimulus.Type == SightSenseID)
		{
			const bool bSightSensed = Stimulus.WasSuccessfullySensed();
			bCanSeeTarget |= bSightSensed;
			if (bSightSensed)
			{
				LastKnownLocation = Actor->GetActorLocation();
			}
		}
		else if (Stimulus.Type == HearingSenseID)
		{
			const bool bHearingSensed = Stimulus.WasSuccessfullySensed();
			bHasHeardTarget |= bHearingSensed;
			if (bHearingSensed)
			{
				LastKnownLocation = Stimulus.StimulusLocation;
			}
		}
	}

	SetCurrentTargetActor((bCanSeeTarget || bHasHeardTarget) ? Actor : nullptr);
	TargetInfo.bCanSeeTarget = bCanSeeTarget;
	TargetInfo.bHasHeardTarget = bHasHeardTarget;
	TargetInfo.LastKnownLocation = LastKnownLocation;
	TargetInfo.bHasLastKnownLocation = TargetInfo.bHasLastKnownLocation || bCanSeeTarget || bHasHeardTarget;
}
