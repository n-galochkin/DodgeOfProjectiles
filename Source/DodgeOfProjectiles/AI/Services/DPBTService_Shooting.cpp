#include "DPBTService_Shooting.h"

#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIController.h"
#include "DodgeOfProjectiles/FirstPersonTemplate/FirstPersonWeaponComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UDPBTService_Shooting::UDPBTService_Shooting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Shooting";

	bTickIntervals = true;

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UDPBTService_Shooting, BlackboardKey), AActor::StaticClass());
}

void UDPBTService_Shooting::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AAIController* OwnerController = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (OwnerController == nullptr || Blackboard == nullptr)
	{
		return;
	}

	const AActor* TargetActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
	const APawn* OwningPawn = OwnerController->GetPawn();
	if (!TargetActor || !OwningPawn)
	{
		return;
	}

	FDPBTService_ShootingNodeMemory* MyMemory = reinterpret_cast<FDPBTService_ShootingNodeMemory*>(NodeMemory);

	MyMemory->Timer += DeltaSeconds;

	if (MyMemory->Timer >= MyMemory->Cooldown)
	{
		const bool bIsLookingForTarget = IsLookingForTarget(TargetActor, OwningPawn);
		const bool bIsTargetVisible = IsTargetVisible(TargetActor, OwningPawn);

		if (bIsLookingForTarget && bIsTargetVisible)
		{
			const auto WeaponComponent = OwningPawn->FindComponentByClass<UFirstPersonWeaponComponent>();
			if (ensureMsgf(WeaponComponent != nullptr, TEXT("No weapon component found for %s"), *OwningPawn->GetName()))
			{
				WeaponComponent->Fire();
			}

			MyMemory->Timer = 0.f;
			MyMemory->Cooldown = FMath::FRandRange(BaseCooldown - CooldownRandomDeviation, BaseCooldown + CooldownRandomDeviation); // Новый кулдаун с отклонением
		}
	}
}

bool UDPBTService_Shooting::IsLookingForTarget(const AActor* TargetActor, const APawn* OwningPawn)
{
	const FVector PawnLocation = OwningPawn->GetActorLocation();
	const FVector PawnForward = OwningPawn->GetActorForwardVector();
	const FVector ToTarget = (TargetActor->GetActorLocation() - PawnLocation).GetSafeNormal();

	const float DotProduct = FVector::DotProduct(PawnForward, ToTarget);
	const float CosThreshold = FMath::Cos(FMath::DegreesToRadians(20.0f));

	return DotProduct > CosThreshold;
}

bool UDPBTService_Shooting::IsTargetVisible(const AActor* TargetActor, const APawn* OwningPawn)
{
	FHitResult HitResult;
	const FVector StartLocation = OwningPawn->GetActorLocation() + FVector(0, 0, 70.0f);
	const FVector EndLocation = TargetActor->GetActorLocation();

	const bool bGotHit = UKismetSystemLibrary::LineTraceSingle(
		OwningPawn,
		StartLocation,
		EndLocation,
		{UEngineTypes::ConvertToTraceType(ECC_PhysicsBody)},
		true,
		{const_cast<APawn*>(OwningPawn)},
		EDrawDebugTrace::None,
		HitResult, true);

	return bGotHit && HitResult.GetActor() == TargetActor;
}

FString UDPBTService_Shooting::GetStaticDescription() const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();

	return FString::Printf(
		TEXT("Service: Shooting at target ('%s')\nBase cooldown: %.2f s, Cooldown deviation: %.2f s."),
		*KeyDesc,
		BaseCooldown,
		CooldownRandomDeviation
	);
}