#include "GA_Attack_Basic.h"
#include "HeroCharacter.h"
#include "HeroProjectile.h"
#include "MyGameplayTags.h"
#include "GameFramework/PlayerController.h"

UGA_Attack_Basic::UGA_Attack_Basic()
{
	// 이 어빌리티의 태그 설정
	FGameplayTagContainer NewAssetTags;
	NewAssetTags.AddTag(MyGameplayTags::Player_Ability_Attack_Basic);
	SetAssetTags(NewAssetTags);
}

void UGA_Attack_Basic::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AHeroCharacter* Hero = GetHeroCharacterFromActorInfo();
	if (!Hero || !ProjectileClass)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UGA_Attack_Basic::SpawnProjectile()
{
	AHeroCharacter* Hero = GetHeroCharacterFromActorInfo();
	if (!Hero) return;
	UE_LOG(LogTemp, Warning, TEXT("SpawnProjectile"));
	// 서버에서만 발사체 스폰
	if (GetActorInfo().IsNetAuthority())
	{
		// 발사체 스폰 위치와 방향 설정 (캐릭터 앞쪽)
		FVector SpawnLocation = Hero->GetActorLocation() + Hero->GetActorForwardVector() * 100.f;
		FRotator SpawnRotation = Hero->GetActorRotation();

		// 발사체 스폰
		if (AHeroProjectile* Projectile = GetWorld()->SpawnActor<AHeroProjectile>(ProjectileClass, SpawnLocation, SpawnRotation))
		{
			Projectile->SetOwner(Hero); // 발사체의 주인을 캐릭터로 설정
		}
	}
}
