#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "DPAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class UDPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UDPAttributeSet();
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, Damage);

protected:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;

	bool bOutOfHealth;

	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
};
