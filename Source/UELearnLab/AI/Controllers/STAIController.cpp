#include "AI/Controllers/STAIController.h"

#include "GameplayStateTreeModule/Public/Components/StateTreeAIComponent.h"

ASTAIController::ASTAIController()
{
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));
}

void ASTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (StateTreeAIComponent && !StateTreeAIComponent->IsRunning())
	{
		StateTreeAIComponent->StartLogic();
	}
}
