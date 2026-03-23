#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacterBase.generated.h"

class ATargetPoint;

UCLASS()
class UELEARNLAB_API AAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacterBase();

	bool TryGetNextPatrolLocation(FVector& OutPatrolLocation);
	void ResetPatrolRoute();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI|Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI|Patrol")
	int32 CurrentPatrolIndex = 0;
};
