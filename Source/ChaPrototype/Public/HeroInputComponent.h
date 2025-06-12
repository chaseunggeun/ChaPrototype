// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputDataConfig.h"
#include "HeroInputComponent.generated.h"


UCLASS()
class CHAPROTOTYPE_API UHeroInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UInputDataConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	// 네이티브 입력 액션을 바인딩하는 함수.

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UInputDataConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc );
};


template <class UserObject, typename CallbackFunc>
inline void UHeroInputComponent::BindNativeInputAction(const UInputDataConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding")); // 입력 설정 데이터 에셋이 null인지 확인.

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag)) // 태그로 액션을 찾음.
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func); // 찾은 액션을 바인딩함.
	}
}

template <class UserObject, typename CallbackFunc>
inline void UHeroInputComponent::BindAbilityInputAction(const UInputDataConfig* InInputConfig,
	UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null"));

	// AbilityInputActions 배열을 순회하면서 각 입력을 바인딩합니다
	for (const FHeroInputActionConfig& AbilityInputAction : InInputConfig->AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag.IsValid())
		{
			// 키가 눌렸을 때(Started)와 떼어졌을 때(Completed)를 각각 바인딩합니다
			if (InputPressedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputAction.InputTag);
			}

			if (InputReleasedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputAction.InputTag);
			}
		}
	}
}