// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	// GroundSpeed 계산
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// bHasAcceleration 계산
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared() > 0.f;

	// Direction 계산 로직
	if (GroundSpeed > 0.f)
	{
		// 이동 방향 벡터
		const FVector VelocityNormal = OwningCharacter->GetVelocity().GetSafeNormal2D();

		// 캐릭터의 전방 벡터를 구하고, 수평(XY) 평면에 투영하여 정규화
		FVector ForwardVector = OwningCharacter->GetActorForwardVector();
		ForwardVector.Z = 0.f; // Z값을 0으로 만들어 수평 방향만 남김
		ForwardVector.Normalize(); // 다시 정규화하여 정확한 2D 방향 벡터로 만듬

		// DotProduct 값을 계산하고, 반드시 -1과 1 사이로 제한
		double DotProduct = FVector::DotProduct(ForwardVector, VelocityNormal);
		DotProduct = FMath::Clamp(DotProduct, -1.0, 1.0);
		
		const double AngleInRadians = FMath::Acos(DotProduct);
		Direction = FMath::RadiansToDegrees(AngleInRadians);

		const FVector CrossProduct = FVector::CrossProduct(ForwardVector, VelocityNormal);
		if (CrossProduct.Z < 0.f)
		{
			Direction *= -1.f;
		}
	}
	else
	{
		Direction = 0.f;
	}
}