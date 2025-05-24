// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "DPAIController.generated.h"

UCLASS()
class DODGEOFPROJECTILES_API ADPAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADPAIController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	FName BlackboardKey_Target;

private:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);
};
