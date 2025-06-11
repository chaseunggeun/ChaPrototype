// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHAPROTOTYPE_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHeroPlayerController();

protected:
	virtual void Tick(float DeltaTime) override;
};
