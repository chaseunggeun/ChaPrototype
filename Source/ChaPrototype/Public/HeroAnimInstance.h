// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "HeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHAPROTOTYPE_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	float GroundSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | State")
	bool bHasAcceleration;

private:
	UPROPERTY()
	TObjectPtr<class ACharacter> OwningCharacter;

	UPROPERTY()
	TObjectPtr<class UCharacterMovementComponent> OwningMovementComponent;
};