// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputDataConfig.h"
#include "Kismet/KismetMathLibrary.h"

AHeroCharacter::AHeroCharacter()
{
	// -- 캐릭터 설정 변경 --
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // 회전 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 최대 걷기 속도 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 걷기 중 감속도 설정

	// -- 스프링 암 설정 변경 (쿼터뷰) --
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f; // 카메라를 더 멀리 배치
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f)); // 정해진 각도로 내려다보도록 고정
	SpringArm->bUsePawnControlRotation = false; // 컨트롤러 회전을 스프링 암에 적용하지 않음
	SpringArm->bDoCollisionTest = false; // 바닥이나 벽에 카메라가 부딪히지 않도록 충돌 테스트 비활성화
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	// -- 카메라 설정 변경 --
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // 카메라 역시 직접 회전하지 않음
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input Component로 캐스팅
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 입력 액션 바인딩
		if (InputDataConfig)
		{
			EnhancedInputComponent->BindAction(InputDataConfig->MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Move);
			EnhancedInputComponent->BindAction(InputDataConfig->JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(InputDataConfig->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		// 이 캐릭터의 컨트롤러가 로컬 플레이어 컨트롤러인지 확인
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			// 로컬 플레이어의 Enhanced Input 서브시스템을 가져옴
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				// 기본 매핑 컨텍스트를 추가
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AHeroCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 쿼터뷰에서는 고정된 월드 축을 기준으로 이동
		const FVector ForwardDirection = FVector(1.0f, 0.0f, 0.0f); // 월드의 X축
		const FVector RightDirection = FVector(0.0f, 1.0f, 0.0f); // 월드의 Y축

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
