#pragma once

#include "CoreMinimal.h"
#include "AI/Common/AIConstants.h"
#include "StateTreeEvaluatorBase.h"
#include "STEvaluator_UpdateTargetInfo.generated.h"

class AActor;
struct FStateTreeExecutionContext;

USTRUCT()
struct UELEARNLAB_API FSTEvaluator_UpdateTargetInfoInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<AActor> TargetActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Output")
	float DistanceToTarget = UELearnLabAI::InvalidTargetDistance;
};

USTRUCT(meta = (DisplayName = "Update Target Info"))
struct UELEARNLAB_API FSTEvaluator_UpdateTargetInfo : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTEvaluator_UpdateTargetInfoInstanceData;

	virtual const UStruct* GetInstanceDataType() const override;

	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

private:
	void Update(FStateTreeExecutionContext& Context) const;
};
