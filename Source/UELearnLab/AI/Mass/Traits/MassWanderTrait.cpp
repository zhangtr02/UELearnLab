#include "AI/Mass/Traits/MassWanderTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityUtils.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"

void UMassWanderTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);

	BuildContext.AddFragment<FTransformFragment>();
	BuildContext.AddFragment<FMassVelocityFragment>();
	BuildContext.AddFragment<FMassWanderTargetFragment>();
	BuildContext.AddTag<FMassWanderTag>();

	const FConstSharedStruct WanderParametersFragment = EntityManager.GetOrCreateConstSharedFragment(WanderParameters);
	BuildContext.AddConstSharedFragment(WanderParametersFragment);
}
