#pragma once

#include "CoreMinimal.h"
#include "AI/Mass/Fragments/MassWanderFragments.h"
#include "MassEntityTraitBase.h"
#include "MassWanderTrait.generated.h"

UCLASS(meta = (DisplayName = "UELearnLab Mass Wander"))
class UELEARNLAB_API UMassWanderTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Wander")
	FMassWanderParameters WanderParameters;
};
