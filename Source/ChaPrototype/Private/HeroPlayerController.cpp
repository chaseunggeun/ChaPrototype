// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

AHeroPlayerController::AHeroPlayerController()
{
	bShowMouseCursor = true; // 마우스 커서 활성화
	DefaultMouseCursor = EMouseCursor::Type::Default;
}

void AHeroPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 이 컨트롤러가 조종하는 폰(캐릭터)을 가져옵니다
	APawn* const ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		FHitResult HitResult;
		// 마우스 커서 아래에 있는 오브젝트 정보를 가져옵니다 (ECC_Visibility 채널 사용)
		if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			// 캐릭터의 위치에서 마우스 커서가 찍힌 위치를 향하는 방향 벡터를 계산합니다
			FVector LookDirection = HitResult.ImpactPoint - ControlledPawn->GetActorLocation();
			LookDirection.Z = 0.f; // 캐릭터가 위아래로 기울지 않도록 Z축 값을 0으로 고정합니다

			// 계산된 방향 벡터를 FRotator 회전 값으로 변환합니다
			const FRotator TargetRotation = LookDirection.Rotation();

          FRotator SmoothRotation = FMath::RInterpTo(this->GetControlRotation(), TargetRotation, DeltaTime, 10.0f);
			// 컨트롤러의 회전 값을 목표 지점으로 설정합니다
			// 캐릭터의 bUseControllerRotationYaw가 true이면 이 회전 값을 따라 캐릭터가 회전합니다
			this->SetControlRotation(SmoothRotation);
		}
	}
}
