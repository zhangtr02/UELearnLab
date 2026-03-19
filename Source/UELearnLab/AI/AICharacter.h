

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

class ATargetPoint;

UCLASS()
class UELEARNLAB_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();
	
	UPROPERTY(EditInstanceOnly, Category="AI")
	TArray<ATargetPoint*> PatrolPoints;
	
	int32 CurrentPatrolIndex = 0;
};
