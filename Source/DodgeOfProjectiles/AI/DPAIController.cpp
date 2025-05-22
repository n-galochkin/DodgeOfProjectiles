
#include "DPAIController.h"


ADPAIController::ADPAIController()
{
}

void ADPAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}
