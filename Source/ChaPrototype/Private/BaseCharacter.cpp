#include "BaseCharacter.h"
#include "BasePlayerState.h" // PlayerState 클래스 참조가 필수
#include "AbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter()
{
    // ASC와 AttributeSet 생성 코드가 제거되어 생성자가 매우 깔끔해졌습니다
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
    // 캐릭터가 직접 ASC를 갖는 대신, PlayerState를 통해 가져옵니다
    ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
    return PS ? PS->GetAbilitySystemComponent() : nullptr;
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
    if (PS)
    {
        // [핵심] ASC의 주인을 PlayerState로, 아바타를 이 캐릭터로 설정
        // 이를 통해 ASC는 PlayerState에 영구히 존재하고, 캐릭터는 일시적인 아바타가 됩니다
        PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

        // 초기화 함수 호출
        InitializeAttributes();
        GrantDefaultAbilities();
    }
}

void ABaseCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
    if (PS)
    {
        // 클라이언트에서도 Owner와 Avatar 정보를 정확히 동기화합니다
        PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
    }
}

void ABaseCharacter::InitializeAttributes()
{
    // PlayerState로부터 ASC를 가져옵니다
    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
    if (!ASC || !DefaultAttributeEffect)
    {
        return;
    }

    FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
    if (SpecHandle.IsValid())
    {
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }
}

void ABaseCharacter::GrantDefaultAbilities()
{
    // PlayerState로부터 ASC를 가져옵니다
    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
    {
        if (AbilityClass)
        {
            ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass));
        }
    }
}