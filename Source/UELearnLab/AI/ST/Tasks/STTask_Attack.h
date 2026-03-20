#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "STTask_Attack.generated.h"

USTRUCT()
struct UELEARNLAB_API FSTTask_Attack_InstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Config")
	float DebugMessageTime = 1.5f;
};

USTRUCT(meta = (DisplayName = "Attack"))
struct UELEARNLAB_API FSTTask_Attack : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTTask_Attack_InstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FSTTask_Attack_InstanceData::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};