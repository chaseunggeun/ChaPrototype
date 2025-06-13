// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroGameplayAbility.h"
#include "GA_Attack_Basic.generated.h"

/**
 * 
 */
class AHeroProjectile;

UCLASS()
class CHAPROTOTYPE_API UGA_Attack_Basic : public UHeroGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Attack_Basic();

protected:
	// 어빌리티 활성화 시 호출
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	// 스폰할 발사체 클래스
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TSubclassOf<AHeroProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SpawnProjectile();
	
};
