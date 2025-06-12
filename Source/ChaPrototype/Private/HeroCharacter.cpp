// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeroInputComponent.h"
#include "InputDataConfig.h"
#include "MyGameplayTags.h"
#include "HeroAbilitySystemComponent.h"
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

	checkf(InputConfigDataAsset, TEXT("에셋 할당 확인 ㄱㄱ")); // 입력 설정 데이터 에셋이 할당되었는지 확인.

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer(); // 로컬 플레이어 가져옴.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer); // Enhanced Input 서브시스템 가져옴.

	check(Subsystem); // 서브시스템이 유효한지 확인.

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0); // 기본 매핑 컨텍스트를 추가함.

	UHeroInputComponent* HeroInputComp = CastChecked<UHeroInputComponent>(PlayerInputComponent);

	HeroInputComp->BindNativeInputAction(InputConfigDataAsset, MyGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	HeroInputComp->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, & ThisClass::Input_AbilityInputReleased);
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AHeroCharacter::GrantDefaultAbilities()
{
	// 우리 커스텀 ASC를 가져옵니다
	if (UHeroAbilitySystemComponent* HeroASC = Cast<UHeroAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		// 에디터에서 설정한 매핑 정보를 이용해 어빌리티를 부여합니다
		TArray<FGameplayAbilitySpecHandle> TempHandles;
		HeroASC->GrantHeroAbilities(DefaultMappedAbilities, 1, TempHandles);
	}
}

void AHeroCharacter::Input_Move(const FInputActionValue& Value)
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

void AHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	// 커스텀 ASC로 캐스팅해서 함수를 호출합니다
	if (UHeroAbilitySystemComponent* HeroASC = Cast<UHeroAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		HeroASC->OnAbilityInputPressed(InInputTag);
	}
}

void AHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	if (UHeroAbilitySystemComponent* HeroASC = Cast<UHeroAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		HeroASC->OnAbilityInputReleased(InInputTag);
	}
}