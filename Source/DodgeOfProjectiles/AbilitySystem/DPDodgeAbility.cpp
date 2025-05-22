
#include "DPDodgeAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"

void UDPDodgeAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		const ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
		if (Character && DodgeMontage)
		{
			if (UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance())
			{
				AnimInstance->Montage_Play(DodgeMontage);
				
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
