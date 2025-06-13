// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_AttackDamageExecCalc.generated.h"

/**
 * 
 */
UCLASS()
class CHAPROTOTYPE_API UGE_AttackDamageExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGE_AttackDamageExecCalc();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};