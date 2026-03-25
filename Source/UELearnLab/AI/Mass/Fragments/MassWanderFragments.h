#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MassWanderFragments.generated.h"

USTRUCT()
struct UELEARNLAB_API FMassWanderTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct UELEARNLAB_API FMassWanderTargetFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Mass")
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "Mass")
	float WaitTimeRemaining = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Mass")
	bool bHasTarget = false;
};

USTRUCT()
struct UELEARNLAB_API FMassWanderParameters : public FMassConstSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mass", meta = (ClampMin = "0.0", ForceUnits = "cm"))
	float SearchRadius = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Mass", meta = (ClampMin = "0.0", ForceUnits = "cm/s"))
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Mass", meta = (ClampMin = "0.0", ForceUnits = "cm"))
	float ArrivalDistance = 80.0f;

	UPROPERTY(EditAnywhere, Category = "Mass", meta = (ClampMin = "0.0", ForceUnits = "s"))
	float WaitTime = 1.5f;
};
