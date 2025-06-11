// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class CHAPROTOTYPE_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// IAbilitySystemInterface 오버라이드
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// 캐릭터가 컨트롤러에 의해 빙의될 때 서버에서 호출
	virtual void PossessedBy(AController* NewController) override;
	
	// 플레이어 상태가 리플리케이트될 때 클라이언트에서 호출
	virtual void OnRep_PlayerState() override;

	// 캐릭터 생성 시 적용할 기본 어트리뷰트 값 (체력, 속도 등)
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS | Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	// 캐릭터 생성 시 부여할 기본 어빌리티 (공격, 점프 등)
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS | Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	// 어트리뷰트를 초기화하는 헬퍼 함수
	void InitializeAttributes();

	// 기본 어빌리티를 부여하는 헬퍼 함수
	void GrantDefaultAbilities();
};
