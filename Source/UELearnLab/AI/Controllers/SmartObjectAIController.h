#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/BTAIController.h"
#include "SmartObjectRequestTypes.h"
#include "SmartObjectRuntime.h"
#include "SmartObjectSubsystem.h"
#include "SmartObjectAIController.generated.h"

UCLASS()
class UELEARNLAB_API ASmartObjectAIController : public ABTAIController
{
	GENERATED_BODY()

public:
	ASmartObjectAIController();

	bool UpdateSmartObjectCandidate(float SearchRadius);
	bool ClaimSmartObject();
	bool ReleaseSmartObject();
	void ResetSmartObjectState();

	bool HasAvailableSmartObject() const;
	bool HasClaimedSmartObject() const;
	FVector GetSmartObjectLocation(const FVector& FallbackLocation = FVector::ZeroVector) const;

protected:
	USmartObjectSubsystem* GetSmartObjectSubsystem() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SmartObject")
	FSmartObjectRequestResult CurrentSmartObjectRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SmartObject")
	FVector CurrentSmartObjectLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SmartObject")
	bool bHasSmartObjectLocation = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SmartObject")
	FSmartObjectClaimHandle CurrentSmartObjectClaimHandle;
};
