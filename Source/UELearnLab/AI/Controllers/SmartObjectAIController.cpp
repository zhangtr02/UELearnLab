#include "AI/Controllers/SmartObjectAIController.h"

ASmartObjectAIController::ASmartObjectAIController()
{
}

bool ASmartObjectAIController::UpdateSmartObjectCandidate(const float SearchRadius)
{
	if (HasClaimedSmartObject())
	{
		return true;
	}

	APawn* ControlledPawn = GetPawn();
	USmartObjectSubsystem* SmartObjectSubsystem = GetSmartObjectSubsystem();
	if (!ControlledPawn || !SmartObjectSubsystem)
	{
		ResetSmartObjectState();
		return false;
	}

	const FVector SearchOrigin = ControlledPawn->GetActorLocation();
	const FVector SearchExtent(SearchRadius);

	FSmartObjectRequestFilter RequestFilter;
	RequestFilter.ClaimPriority = ESmartObjectClaimPriority::Normal;

	const FSmartObjectRequest Request(FBox::BuildAABB(SearchOrigin, SearchExtent), RequestFilter);
	const FSmartObjectRequestResult RequestResult = SmartObjectSubsystem->FindSmartObject(Request, ControlledPawn);
	if (!RequestResult.IsValid())
	{
		ResetSmartObjectState();
		return false;
	}

	FSmartObjectSlotEntranceLocationRequest EntranceRequest;
	EntranceRequest.UserActor = ControlledPawn;
	EntranceRequest.SearchLocation = SearchOrigin;
	EntranceRequest.bUseSlotLocationAsFallback = true;

	FSmartObjectSlotEntranceLocationResult EntranceLocation;
	if (!SmartObjectSubsystem->FindEntranceLocationForSlot(RequestResult.SlotHandle, EntranceRequest, EntranceLocation))
	{
		ResetSmartObjectState();
		return false;
	}

	CurrentSmartObjectRequest = RequestResult;
	CurrentSmartObjectLocation = EntranceLocation.Location;
	bHasSmartObjectLocation = EntranceLocation.bIsValid;
	return true;
}

bool ASmartObjectAIController::ClaimSmartObject()
{
	if (HasClaimedSmartObject())
	{
		return true;
	}

	if (!CurrentSmartObjectRequest.IsValid())
	{
		return false;
	}

	USmartObjectSubsystem* SmartObjectSubsystem = GetSmartObjectSubsystem();
	if (!SmartObjectSubsystem)
	{
		return false;
	}

	CurrentSmartObjectClaimHandle = SmartObjectSubsystem->MarkSlotAsClaimed(
		CurrentSmartObjectRequest.SlotHandle,
		ESmartObjectClaimPriority::Normal
	);

	return CurrentSmartObjectClaimHandle.IsValid();
}

bool ASmartObjectAIController::ReleaseSmartObject()
{
	if (!CurrentSmartObjectClaimHandle.IsValid())
	{
		ResetSmartObjectState();
		return false;
	}

	USmartObjectSubsystem* SmartObjectSubsystem = GetSmartObjectSubsystem();
	if (!SmartObjectSubsystem)
	{
		ResetSmartObjectState();
		return false;
	}

	const bool bReleased = SmartObjectSubsystem->MarkSlotAsFree(CurrentSmartObjectClaimHandle);
	ResetSmartObjectState();
	return bReleased;
}

void ASmartObjectAIController::ResetSmartObjectState()
{
	CurrentSmartObjectRequest = FSmartObjectRequestResult();
	CurrentSmartObjectLocation = FVector::ZeroVector;
	bHasSmartObjectLocation = false;
	CurrentSmartObjectClaimHandle.Invalidate();
}

bool ASmartObjectAIController::HasAvailableSmartObject() const
{
	return CurrentSmartObjectRequest.IsValid() && bHasSmartObjectLocation;
}

bool ASmartObjectAIController::HasClaimedSmartObject() const
{
	return CurrentSmartObjectClaimHandle.IsValid();
}

FVector ASmartObjectAIController::GetSmartObjectLocation(const FVector& FallbackLocation) const
{
	return HasAvailableSmartObject() ? CurrentSmartObjectLocation : FallbackLocation;
}

USmartObjectSubsystem* ASmartObjectAIController::GetSmartObjectSubsystem() const
{
	return GetWorld() ? USmartObjectSubsystem::GetCurrent(GetWorld()) : nullptr;
}
