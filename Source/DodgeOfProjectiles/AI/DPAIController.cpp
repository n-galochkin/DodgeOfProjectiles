
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
}

void ADPAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.IsActive())
	{
		Blackboard->SetValueAsObject(BlackboardKey_Target, Actor);

		GetWorld()->GetTimerManager().ClearTimer(LostTargetTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(LostTargetTimerHandle, this, &ADPAIController::OnLostTargetTimerEnded, 5.0f, false);
	}
}

void ADPAIController::OnLostTargetTimerEnded()
{
	Blackboard->SetValueAsObject(BlackboardKey_Target, nullptr);
}
