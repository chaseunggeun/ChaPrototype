// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "HeroAbilitySystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FHeroAbilityMapping
{
	GENERATED_BODY()

	// 부여할 어빌리티 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayAbility> AbilityClass;

	// 이 어빌리티를 발동시킬 입력 태그입니다
	// 비워두면(None) 입력이 없는 패시브 어빌리티로 취급됩니다
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};


UCLASS()
class CHAPROTOTYPE_API UHeroAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// 1. 입력 처리 함수 (이전과 동일)
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	// 2. 어빌리티 부여 및 제거 함수 (인자 타입 변경)
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantHeroAbilities(const TArray<FHeroAbilityMapping>& InAbilitiesToGrant, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RemovedGrantedHeroAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};