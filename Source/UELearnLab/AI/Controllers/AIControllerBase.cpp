#include "AI/Controllers/AIControllerBase.h"

#include "AI/Characters/AICharacterBase.h"
#include "AI/EQS/Components/EQSQueryComponent.h"
#include "Core/UELearnLabCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIControllerBase::AAIControllerBase()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	SetPerceptionComponent(*AIPerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	EQSQueryComponent = CreateDefaultSubobject<UEQSQueryComponent>(TEXT("EQSQueryComponent"));
	InitializeSightConfig();
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComp)
	{
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerBase::HandleTargetPerceptionUpdated);
	}
}

float AAIControllerBase::GetDistanceToTarget(const float InvalidDistance) const
{
	const APawn* ControlledPawn = GetPawn();
	const AActor* TargetActor = GetCurrentTargetActor();

	if (!ControlledPawn || !TargetActor)
	{
		return InvalidDistance;
	}

	return FVector::Dist(
		ControlledPawn->GetActorLocation(),
		TargetActor->GetActorLocation()
	);
}

AAICharacterBase* AAIControllerBase::GetControlledAICharacter() const
{
	return Cast<AAICharacterBase>(GetPawn());
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

	ProcessTargetPerception(Actor, Stimulus);
}

void AAIControllerBase::ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		SetCurrentTargetActor(Actor);
	}
	else if (CurrentTargetActor == Actor)
	{
		SetCurrentTargetActor(nullptr);
	}
}

void AAIControllerBase::InitializeSightConfig()
{
	if (!AIPerceptionComp || !SightConfig)
	{
		return;
	}

	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1800.0f;
	SightConfig->PeripheralVisionAngleDegrees = 70.0f;
	SightConfig->SetMaxAge(2.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AAIControllerBase::SetCurrentTargetActor(AActor* NewTargetActor)
{
	if (CurrentTargetActor == NewTargetActor)
	{
		return;
	}

	CurrentTargetActor = NewTargetActor;
	OnTargetActorUpdated(NewTargetActor);
}

void AAIControllerBase::OnTargetActorUpdated(AActor* NewTargetActor)
{
}
