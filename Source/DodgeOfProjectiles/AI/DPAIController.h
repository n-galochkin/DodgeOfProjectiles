// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI" )
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
