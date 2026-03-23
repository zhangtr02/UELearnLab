
#include "AI/Characters/AICharacterBase.h"

#include "Engine/TargetPoint.h"

AAICharacterBase::AAICharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

bool AAICharacterBase::TryGetNextPatrolLocation(FVector& OutPatrolLocation)
{
	const int32 NumPatrolPoints = PatrolPoints.Num();
	if (NumPatrolPoints == 0)
	{
		return false;
	}

	if (!PatrolPoints.IsValidIndex(CurrentPatrolIndex))
	{
		CurrentPatrolIndex = 0;
	}

	for (int32 Offset = 0; Offset < NumPatrolPoints; ++Offset)
	{
		const int32 PatrolIndex = (CurrentPatrolIndex + Offset) % NumPatrolPoints;
		const ATargetPoint* PatrolPoint = PatrolPoints[PatrolIndex];
		if (!PatrolPoint)
		{
			continue;
		}

		OutPatrolLocation = PatrolPoint->GetActorLocation();
		CurrentPatrolIndex = (PatrolIndex + 1) % NumPatrolPoints;
		return true;
	}

	return false;
}

void AAICharacterBase::ResetPatrolRoute()
{
	CurrentPatrolIndex = 0;
}
