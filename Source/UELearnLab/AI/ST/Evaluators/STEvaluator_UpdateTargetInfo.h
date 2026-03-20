#pragma once

#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionContext.h"
#include "AI/Controllers/STAIController.h"
#include "STEvaluator_UpdateTargetInfo.generated.h"

USTRUCT()
struct UELEARNLAB_API FSTEvaluator_UpdateTargetInfoInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Output")
	TObjectPtr<AActor> TargetActor = nullptr;

	UPROPERTY(EditAnywhere, Category="Output")
	float DistanceToTarget = 999999.0f;
};

USTRUCT(meta = (DisplayName = "Update Target Info"))
struct UELEARNLAB_API FSTEvaluator_UpdateTargetInfo : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTEvaluator_UpdateTargetInfoInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FSTEvaluator_UpdateTargetInfoInstanceData::StaticStruct();
	}

	virtual void TreeStart(FStateTreeExecutionContext& Context) const override
	{
		Update(Context);
	}

	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override
	{
		Update(Context);
	}

	void Update(const FStateTreeExecutionContext& Context) const
	{
		FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

		InstanceData.TargetActor = nullptr;
		InstanceData.DistanceToTarget = 999999.0f;
		
		UObject* OwnerObject = Context.GetOwner();
		const ASTAIController* OwnerController = Cast<ASTAIController>(OwnerObject);

		if (!OwnerController)
		{
			return;
		}
		
		const APawn* OwnerPawn = OwnerController->GetPawn();
		
		if (!OwnerPawn)
		{
			return;
		}
		
		AActor* CurrentTarget = OwnerController->GetCurrentTargetActor();
		InstanceData.TargetActor = CurrentTarget;

		if (!CurrentTarget)
		{
			return;
		}

		InstanceData.DistanceToTarget =
			FVector::Dist(OwnerPawn->GetActorLocation(), CurrentTarget->GetActorLocation());
		
	}
};
