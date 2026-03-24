#include "AI/Controllers/TeamAIController.h"

ATeamAIController::ATeamAIController()
{
}

FGenericTeamId ATeamAIController::GetGenericTeamId() const
{
	return UELearnLabTeam::ToGenericTeamId(TeamId);
}

ETeamAttitude::Type ATeamAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = UELearnLabTeam::ResolveTeamAgent(&Other);
	if (!OtherTeamAgent)
	{
		return ETeamAttitude::Neutral;
	}

	const FGenericTeamId SelfTeamId = GetGenericTeamId();
	const FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();

	if (OtherTeamId == FGenericTeamId::NoTeam || SelfTeamId == FGenericTeamId::NoTeam)
	{
		return ETeamAttitude::Neutral;
	}

	if (SelfTeamId == OtherTeamId)
	{
		return ETeamAttitude::Friendly;
	}

	return ETeamAttitude::Hostile;
}

ETeamLabId ATeamAIController::GetActorTeamId(const AActor* Actor) const
{
	const IGenericTeamAgentInterface* TeamAgent = UELearnLabTeam::ResolveTeamAgent(Actor);
	if (!TeamAgent)
	{
		return ETeamLabId::Neutral;
	}

	return UELearnLabTeam::ToTeamLabId(TeamAgent->GetGenericTeamId());
}

bool ATeamAIController::IsHostileActor(const AActor* Actor) const
{
	return Actor && GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile;
}

bool ATeamAIController::IsValidTargetActor(AActor* Actor) const
{
	return Actor && UELearnLabTeam::ResolveTeamAgent(Actor) != nullptr;
}

void ATeamAIController::ProcessTargetPerception(AActor* Actor, const FAIStimulus& Stimulus)
{
	if (!IsHostileActor(Actor))
	{
		if (GetCurrentTargetActor() == Actor)
		{
			SetCurrentTargetActor(nullptr);
		}

		return;
	}

	Super::ProcessTargetPerception(Actor, Stimulus);
}
