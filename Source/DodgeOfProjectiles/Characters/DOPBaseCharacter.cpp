// Fill out your copyright notice in the Description page of Project Settings.


#include "DOPBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "DodgeOfProjectiles/AbilitySystem/Attributes/DOPAttributeSet.h"
#include "DodgeOfProjectiles/FirstPersonTemplate/FirstPersonWeaponComponent.h"

ADOPBaseCharacter::ADOPBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ADOPBaseCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UDOPAttributeSet>(this));
}

void ADOPBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ADOPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(WeaponClass != nullptr, TEXT("No weapon class specified for %s"), *GetName()))
	{
		WeaponComponent = Cast<UFirstPersonWeaponComponent>(AddComponentByClass(WeaponClass, true, {}, false));
		WeaponComponent->AttachWeapon(this);
	}
}

void ADOPBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADOPBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADOPBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
