#include "HeroProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AHeroProjectile::AHeroProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionComp);
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->SetSphereRadius(15.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent); // 루트 컴포넌트(CollisionComp)에 부착
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메시는 충돌을 처리하지 않도록 설정
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // 중력 영향 안 받음
}

void AHeroProjectile::BeginPlay()
{
	Super::BeginPlay();
	// 충돌 이벤트에 함수 바인딩
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHeroProjectile::OnSphereOverlap);
}

void AHeroProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 자기 자신이나 발사한 주인과는 충돌하지 않도록 처리
    if (OtherActor && OtherActor != GetOwner())
    {
        // 충돌한 액터의 ASC를 가져옴
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
        if (TargetASC && DamageEffectClass)
        {
            // 이펙트를 적용할 컨텍스트를 만들고, 이펙트의 주체(Causer)를 발사한 주인으로 설정
            FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
            EffectContext.AddSourceObject(GetOwner());

            // 이펙트 스펙 생성
            FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffectClass, 1, EffectContext);
            if (SpecHandle.IsValid())
            {
                // 대상에게 이펙트 적용
                TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());	UE_LOG(LogTemp, Warning, TEXT("ProjectileMovement"));

            }
        }
        
        // 충돌 후 발사체 파괴
        Destroy();
    }
}