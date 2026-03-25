#pragma once

#include "CoreMinimal.h"
#include "MassEntityQuery.h"
#include "MassProcessor.h"
#include "MassWanderProcessor.generated.h"

UCLASS()
class UELEARNLAB_API UMassWanderProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UMassWanderProcessor();

protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	bool UpdateWanderTarget(const FVector& OriginLocation, const float SearchRadius, FVector& OutTargetLocation, UWorld& World) const;

protected:
	FMassEntityQuery EntityQuery;
};
