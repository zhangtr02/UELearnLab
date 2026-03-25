#include "AI/Mass/Processors/MassWanderProcessor.h"

#include "AI/Mass/Fragments/MassWanderFragments.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassMovementFragments.h"
#include "NavigationSystem.h"

UMassWanderProcessor::UMassWanderProcessor()
	: EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	bRequiresGameThreadExecution = true;
	ExecutionFlags = static_cast<uint8>(EProcessorExecutionFlags::AllNetModes);
}

void UMassWanderProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassWanderTargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassWanderParameters>(EMassFragmentPresence::All);
	EntityQuery.AddTagRequirement<FMassWanderTag>(EMassFragmentPresence::All);
}

void UMassWanderProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	UWorld* World = Context.GetWorld();
	if (!World)
	{
		return;
	}

	EntityQuery.ForEachEntityChunk(Context, [this, World](FMassExecutionContext& Context)
		{
			const float DeltaTime = Context.GetDeltaTimeSeconds();
			const FMassWanderParameters& WanderParameters = Context.GetConstSharedFragment<FMassWanderParameters>();
			const TArrayView<FTransformFragment> TransformFragments = Context.GetMutableFragmentView<FTransformFragment>();
			const TArrayView<FMassVelocityFragment> VelocityFragments = Context.GetMutableFragmentView<FMassVelocityFragment>();
			const TArrayView<FMassWanderTargetFragment> WanderTargetFragments = Context.GetMutableFragmentView<FMassWanderTargetFragment>();
			const int32 EntityCount = Context.GetNumEntities();

			for (FMassExecutionContext::FEntityIterator EntityIt = Context.CreateEntityIterator(); EntityIt; ++EntityIt)
			{
				FTransform& Transform = TransformFragments[EntityIt].GetMutableTransform();
				FMassVelocityFragment& Velocity = VelocityFragments[EntityIt];
				FMassWanderTargetFragment& WanderTarget = WanderTargetFragments[EntityIt];

				if (WanderTarget.WaitTimeRemaining > 0.0f)
				{
					WanderTarget.WaitTimeRemaining = FMath::Max(0.0f, WanderTarget.WaitTimeRemaining - DeltaTime);
					Velocity.Value = FVector::ZeroVector;
					continue;
				}

				const FVector CurrentLocation = Transform.GetLocation();
				if (!WanderTarget.bHasTarget)
				{
					WanderTarget.bHasTarget = UpdateWanderTarget(
						CurrentLocation,
						WanderParameters.SearchRadius,
						WanderTarget.TargetLocation,
						*World
					);

					if (!WanderTarget.bHasTarget)
					{
						Velocity.Value = FVector::ZeroVector;
						continue;
					}
				}

				const FVector ToTarget = WanderTarget.TargetLocation - CurrentLocation;
				const float DistanceToTarget = ToTarget.Length();
				if (DistanceToTarget <= WanderParameters.ArrivalDistance)
				{
					WanderTarget.bHasTarget = false;
					WanderTarget.WaitTimeRemaining = WanderParameters.WaitTime;
					Velocity.Value = FVector::ZeroVector;
					continue;
				}

				const FVector MoveDirection = ToTarget.GetSafeNormal();
				Velocity.Value = MoveDirection * WanderParameters.MoveSpeed;
				Transform.SetLocation(CurrentLocation + Velocity.Value * DeltaTime);

				if (!MoveDirection.IsNearlyZero())
				{
					Transform.SetRotation(MoveDirection.ToOrientationQuat());
				}
			}
		});
}

bool UMassWanderProcessor::UpdateWanderTarget(
	const FVector& OriginLocation,
	const float SearchRadius,
	FVector& OutTargetLocation,
	UWorld& World) const
{
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(&World);
	if (!NavigationSystem)
	{
		return false;
	}

	FNavLocation NavLocation;
	if (!NavigationSystem->GetRandomReachablePointInRadius(OriginLocation, SearchRadius, NavLocation))
	{
		return false;
	}

	OutTargetLocation = NavLocation.Location;
	return true;
}
