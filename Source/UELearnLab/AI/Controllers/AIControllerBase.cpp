#include "AI/Controllers/AIControllerBase.h"

#include "Core/UELearnLabCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

AAIControllerBase::AAIControllerBase()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 1500.f;
		SightConfig->LoseSightRadius = 1800.f;
		SightConfig->PeripheralVisionAngleDegrees = 70.f;
		SightConfig->SetMaxAge(2.0f);

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComp->ConfigureSense(*SightConfig);
		AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComp)
	{
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerBase::HandleTargetPerceptionUpdated);
	}
}

bool AAIControllerBase::IsValidTargetActor(AActor* Actor) const
{
	return Cast<AUELearnLabCharacter>(Actor) != nullptr;
}

void AAIControllerBase::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
	{
		return;
	}

	if (!IsValidTargetActor(Actor))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		CurrentTargetActor = Actor;
		OnTargetActorUpdated(Actor);
	}
	else
	{
		if (CurrentTargetActor == Actor)
		{
			CurrentTargetActor = nullptr;
			OnTargetActorUpdated(nullptr);
		}
	}
}

void AAIControllerBase::OnTargetActorUpdated(AActor* NewTargetActor)
{
	
}