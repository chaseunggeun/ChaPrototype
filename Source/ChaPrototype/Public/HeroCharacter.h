// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
 class USpringArmComponent;
 class UCameraComponent;
 class UInputMappingContext;
 class UInputDataConfig;
 struct FInputActionValue;
 
UCLASS()
class CHAPROTOTYPE_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AHeroCharacter();

protected:
	// 매 프레임 호출되는 함수. 마우스 방향으로 회전하는 로직을 여기에 넣습니다
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	// -- 플레이어 전용 컴포넌트 --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	// -- 플레이어 전용 입력 설정 --
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputDataConfig> InputDataConfig;

	// -- 입력 처리 함수 --
	void Move(const FInputActionValue& Value);
};