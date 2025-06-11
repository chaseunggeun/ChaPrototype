// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include "ChaPrototype/Public/BaseCharacter.h"


ABasePlayerState::ABasePlayerState()
{
	// ASC 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// 어트리뷰트 셋 생성
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAttributeSet* ABasePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}