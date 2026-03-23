#include "AI/Common/AIDebugHelper.h"

#include "Engine/Engine.h"

void UELearnLabAI::ShowAttackDebugMessage(const float DisplayTime, const FColor DisplayColor)
{
	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		DisplayTime,
		DisplayColor,
		TEXT("Attack!"),
		true,
		FVector2D(3.0f, 3.0f)
	);
}
