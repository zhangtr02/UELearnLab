#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "TeamTypes.generated.h"

UENUM(BlueprintType)
enum class ETeamLabId : uint8
{
	Neutral = 0 UMETA(DisplayName = "Neutral"),
	Red = 1 UMETA(DisplayName = "Red"),
	Blue = 2 UMETA(DisplayName = "Blue")
};

namespace UELearnLabTeam
{
	inline FGenericTeamId ToGenericTeamId(const ETeamLabId TeamId)
	{
		switch (TeamId)
		{
		case ETeamLabId::Red:
			return FGenericTeamId(static_cast<uint8>(ETeamLabId::Red));
		case ETeamLabId::Blue:
			return FGenericTeamId(static_cast<uint8>(ETeamLabId::Blue));
		default:
			return FGenericTeamId::NoTeam;
		}
	}

	inline ETeamLabId ToTeamLabId(const FGenericTeamId TeamId)
	{
		if (TeamId == FGenericTeamId::NoTeam)
		{
			return ETeamLabId::Neutral;
		}

		switch (TeamId.GetId())
		{
		case static_cast<uint8>(ETeamLabId::Red):
			return ETeamLabId::Red;
		case static_cast<uint8>(ETeamLabId::Blue):
			return ETeamLabId::Blue;
		default:
			return ETeamLabId::Neutral;
		}
	}

	inline const IGenericTeamAgentInterface* ResolveTeamAgent(const AActor* Actor)
	{
		if (!Actor)
		{
			return nullptr;
		}

		if (const IGenericTeamAgentInterface* ActorTeamAgent = Cast<const IGenericTeamAgentInterface>(Actor))
		{
			return ActorTeamAgent;
		}

		if (const APawn* Pawn = Cast<APawn>(Actor))
		{
			if (const AController* Controller = Pawn->GetController())
			{
				if (const IGenericTeamAgentInterface* ControllerTeamAgent = Cast<const IGenericTeamAgentInterface>(Controller))
				{
					return ControllerTeamAgent;
				}
			}
		}

		return nullptr;
	}
}
