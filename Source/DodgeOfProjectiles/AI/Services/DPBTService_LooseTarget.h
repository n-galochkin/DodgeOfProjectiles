
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "DPBTService_LooseTarget.generated.h"


/**
 * A service class designed to handle the behavior tree logic for losing a target in a system.
 */
UCLASS(hidecategories=(Service), MinimalAPI)
class UDPBTService_LooseTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	UDPBTService_LooseTarget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere)
	float LooseTargetDistance = 1000;
};
