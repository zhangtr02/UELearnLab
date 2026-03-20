

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
	
	UPROPERTY(EditInstanceOnly, Category="AI")
	TArray<ATargetPoint*> PatrolPoints;
	
	int32 CurrentPatrolIndex = 0;
};
