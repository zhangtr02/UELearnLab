#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "STTask_FindNextPatrolPoint.generated.h"

USTRUCT()
struct UELEARNLAB_API FSTTask_FindNextPatrolPoint_InstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Output")
	FVector PatrolLocation = FVector::ZeroVector;
};

USTRUCT(meta = (DisplayName = "Find Next Patrol Point"))
struct UELEARNLAB_API FSTTask_FindNextPatrolPoint : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTTask_FindNextPatrolPoint_InstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FSTTask_FindNextPatrolPoint_InstanceData::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};