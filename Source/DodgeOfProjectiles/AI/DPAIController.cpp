#include "DPAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"


ADPAIController::ADPAIController()
{
}

void ADPAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADPAIController::OnTargetPerceptionUpdated);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ADPAIController::OnTargetPerceptionForgotten);
}

void ADPAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	PerceptionComponent->OnTargetPerceptionUpdated.RemoveAll(this);
	PerceptionComponent->OnTargetPerceptionForgotten.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void ADPAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	if (Stimulus.IsActive())
	{
		Blackboard->SetValueAsObject(BlackboardKey_Target, Actor);
	}
}

void ADPAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	const AActor* CurrentTarget = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey_Target));

	if (CurrentTarget != nullptr && CurrentTarget == Actor)
	{
		Blackboard->SetValueAsObject(BlackboardKey_Target, nullptr);
	}
}