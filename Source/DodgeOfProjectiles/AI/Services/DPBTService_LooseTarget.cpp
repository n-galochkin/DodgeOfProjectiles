
#include "DPBTService_LooseTarget.h"

#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIController.h"

UDPBTService_LooseTarget::UDPBTService_LooseTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Loose Target By Distance";

	bTickIntervals = true;

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UDPBTService_LooseTarget, BlackboardKey), AActor::StaticClass());
}

void UDPBTService_LooseTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AAIController* OwnerController = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (OwnerController == nullptr || Blackboard == nullptr)
	{
		return;
	}

	const AActor* TargetActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
	const AActor* OwnerActor = OwnerController->GetPawn();

	if (TargetActor && OwnerActor && OwnerActor->GetDistanceTo(TargetActor) > LooseTargetDistance)
	{
		Blackboard->ClearValue(BlackboardKey.GetSelectedKeyID());
	}
}

FString UDPBTService_LooseTarget::GetStaticDescription() const
{
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	}

	return FString::Printf(TEXT("Loose %s By Distance: %f"), *KeyDesc, LooseTargetDistance);
}
