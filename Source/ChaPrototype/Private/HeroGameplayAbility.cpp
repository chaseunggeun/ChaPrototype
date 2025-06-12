// HeroGameplayAbility.cpp

#include "HeroGameplayAbility.h"
#include "HeroCharacter.h"
#include "HeroAbilitySystemComponent.h"

void UHeroGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (ActivationPolicy == EHeroAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && ActorInfo->AbilitySystemComponent.IsValid() && ActorInfo->AbilitySystemComponent->IsOwnerActorAuthoritative())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UHeroGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

AHeroCharacter* UHeroGameplayAbility::GetHeroCharacterFromActorInfo() const
{
	return Cast<AHeroCharacter>(GetAvatarActorFromActorInfo());
}

UHeroAbilitySystemComponent* UHeroGameplayAbility::GetHeroAbilitySystemComponentFromActorInfo() const
{
	return Cast<UHeroAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}