// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HeroGameplayAbility.generated.h"

class UHeroAbilitySystemComponent;
class AHeroCharacter;

// 어빌리티가 어떻게 활성화될지를 정의하는 열거형(Enum)입니다
UENUM(BlueprintType)
enum class EHeroAbilityActivationPolicy : uint8
{
	// 입력이나 게임플레이 이벤트에 의해 발동되는 일반적인 액티브 어빌리티입니다
	OnTriggered,

	// 어빌리티가 캐릭터에게 부여되는 즉시 자동으로 발동되는 패시브 어빌리티입니다
	OnGiven
};


UCLASS()
class CHAPROTOTYPE_API UHeroGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	EHeroAbilityActivationPolicy ActivationPolicy = EHeroAbilityActivationPolicy::OnTriggered;

protected:
	//~ Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	// 헬퍼 함수들은 그대로 유지합니다 (캐싱 대신 사용)
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AHeroCharacter* GetHeroCharacterFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	UHeroAbilitySystemComponent* GetHeroAbilitySystemComponentFromActorInfo() const;
};