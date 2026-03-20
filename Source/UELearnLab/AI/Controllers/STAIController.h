#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/AIControllerBase.h"
#include "STAIController.generated.h"

class UStateTreeAIComponent;

UCLASS()
class UELEARNLAB_API ASTAIController : public AAIControllerBase
{
	GENERATED_BODY()

public:
	ASTAIController();

	UFUNCTION(BlueprintCallable, Category = "AI|ST")
	AActor* GetCurrentTargetActor() const { return CurrentTargetActor; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnTargetActorUpdated(AActor* NewTargetActor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|ST")
	TObjectPtr<UStateTreeAIComponent> StateTreeAIComponent;
};