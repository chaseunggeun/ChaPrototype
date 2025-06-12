// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerState.generated.h"

class UHeroAbilitySystemComponent;
class UBaseAttributeSet;

UCLASS()
class CHAPROTOTYPE_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ABasePlayerState();

	// IAbilitySystemInterface 구현 함수. PlayerState의 ASC를 반환합니다
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// AttributeSet을 가져오는 편의 함수
	UBaseAttributeSet* GetAttributeSet() const;
	
protected:
	// 어빌리티 시스템 컴포넌트(ASC)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHeroAbilitySystemComponent> AbilitySystemComponent;

	// 어트리뷰트 셋
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
};
