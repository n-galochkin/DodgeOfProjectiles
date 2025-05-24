#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "DPBTService_Shooting.generated.h"

struct FDPBTService_ShootingNodeMemory
{
	float Cooldown = 0.f;
	float Timer = 0.f;
};

/**
 * A behavior tree service for handling shooting logic in AI characters.
 */
UCLASS(hidecategories=(Service), MinimalAPI)
class UDPBTService_Shooting : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	UDPBTService_Shooting(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual uint16 GetInstanceMemorySize() const override
	{
		return sizeof(FDPBTService_ShootingNodeMemory);
	}

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, Category="Shooting")
	float BaseCooldown = 0.5f;

	UPROPERTY(EditAnywhere, Category="Shooting")
	float CooldownRandomDeviation = 0.1f;

private:
	static bool IsLookingForTarget(const AActor* TargetActor, const APawn* OwningPawn);

	static bool IsTargetVisible(const AActor* TargetActor, const APawn* OwningPawn);
};
