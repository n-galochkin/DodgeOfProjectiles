// Fill out your copyright notice in the Description page of Project Settings.


#include "DPBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "DodgeOfProjectiles/AbilitySystem/Attributes/DPAttributeSet.h"
#include "DodgeOfProjectiles/FirstPersonTemplate/FirstPersonWeaponComponent.h"

ADPBaseCharacter::ADPBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ADPBaseCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UDPAttributeSet>(this));
}

void ADPBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ADPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(WeaponClass != nullptr, TEXT("No weapon class specified for %s"), *GetName()))
	{
		WeaponComponent = Cast<UFirstPersonWeaponComponent>(AddComponentByClass(WeaponClass, true, {}, false));
		WeaponComponent->AttachWeapon(this);
	}

	if (DodgeAbilityClass)
	{
		FGameplayAbilitySpec DodgeAbilitySpec(DodgeAbilityClass, 1, INDEX_NONE, this);
		AbilitySystemComponent->GiveAbility(DodgeAbilitySpec);
	}

}

void ADPBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADPBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADPBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
