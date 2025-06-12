// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

void UHeroAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	// 모든 활성화 가능한 어빌리티 스펙을 확인합니다
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		// 스펙의 동적 태그에 우리가 찾는 입력 태그가 있는지 확인합니다
		if (Spec.Ability && Spec.GetDynamicSpecSourceTags().HasTagExact(InInputTag))
		{
			Spec.InputPressed = true;
			// 어빌리티가 이미 활성 상태이면, 입력이 눌렸다는 이벤트만 보냅니다
			if (Spec.IsActive())
			{
				if (UGameplayAbility* AbilityInstance = Spec.GetPrimaryInstance())
				{
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
				}
			}
			// 비활성 상태이면, 활성화를 시도합니다
			else
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UHeroAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		// 스펙의 동적 태그에 우리가 찾는 입력 태그가 있는지 확인합니다
		if (Spec.Ability && Spec.GetDynamicSpecSourceTags().HasTagExact(InInputTag))
		{
			Spec.InputPressed = false;
			// 어빌리티가 활성 상태일 때만 입력 해제 이벤트를 보냅니다
			if (Spec.IsActive())
			{
				if (UGameplayAbility* AbilityInstance = Spec.GetPrimaryInstance())
				{
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
				}
			}
		}
	}
}

void UHeroAbilitySystemComponent::GrantHeroAbilities(const TArray<FHeroAbilityMapping>& InAbilitiesToGrant, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	OutGrantedAbilitySpecHandles.Empty();

	// 전달받은 어빌리티 매핑 배열을 순회합니다
	for (const FHeroAbilityMapping& Mapping : InAbilitiesToGrant)
	{
		if (!Mapping.AbilityClass) continue;

		FGameplayAbilitySpec AbilitySpec(Mapping.AbilityClass, ApplyLevel);

		// **핵심: 입력 태그가 유효할 때만(None이 아닐 때만) 동적 태그로 추가합니다**
		if (Mapping.InputTag.IsValid())
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(Mapping.InputTag);
		}

		const FGameplayAbilitySpecHandle GrantedHandle = GiveAbility(AbilitySpec);
		OutGrantedAbilitySpecHandles.Add(GrantedHandle);
	}
}

void UHeroAbilitySystemComponent::RemovedGrantedHeroAbilities(TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	// 제거할 어빌리티 핸들이 담긴 배열을 순회합니다
	for (const FGameplayAbilitySpecHandle& Handle : InSpecHandlesToRemove)
	{
		// 핸들이 유효한지 확인합니다
		if (Handle.IsValid())
		{
			// 이 핸들에 해당하는 어빌리티를 ASC에서 제거합니다
			ClearAbility(Handle);
		}
	}
	
	// 모든 핸들을 사용했으므로, 배열을 비워서 다시 사용하지 않도록 합니다
	InSpecHandlesToRemove.Empty();
}