// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "DPBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ADPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADPBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<class UFirstPersonWeaponComponent> WeaponClass;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UFirstPersonWeaponComponent> WeaponComponent;
};
