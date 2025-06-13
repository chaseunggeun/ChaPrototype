// BaseAttributeSet.cpp
#include "BaseAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Durability, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Speed, COND_None, REPNOTIFY_Always);

	// Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Firepower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);

	// Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

// 전처리
void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		//NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMovementSpeedAttribute())
	{
		// 이동속도가 0 미만으로 떨어지지 않도록 제한
		if (NewValue < 0.f)
		{
			NewValue = 0.f;
		}
	}
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// Health 속성이 변경되었는지 확인합니다.
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// **디버깅 로그 추가**
		// UE_LOG는 에디터의 '출력 로그' 창에 메시지를 표시합니다.
		UE_LOG(LogTemp, Warning, TEXT("Target Health Changed To: %f"), GetHealth());
	}
	UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent();
    
	// 핵심 로직은 서버에서만 실행
	if (TargetASC && TargetASC->IsOwnerActorAuthoritative())
	{
		if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
			
			// 체력이 0 이하일 때의 로직
			if (GetHealth() <= 0.0f)
			{
				// TODO: 캐릭터 사망 처리
			}
		}
	}
}

// OnRep 함수들의 기본 구현
void UBaseAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Attack, OldAttack);
}

void UBaseAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Defense, OldDefense);
}

void UBaseAttributeSet::OnRep_Durability(const FGameplayAttributeData& OldDurability)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Durability, OldDurability);
}

void UBaseAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Speed, OldSpeed);
}

void UBaseAttributeSet::OnRep_Firepower(const FGameplayAttributeData& OldFirepower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Firepower, OldFirepower);
}

void UBaseAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Armor, OldArmor);
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBaseAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UBaseAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Health, OldHealth);
}
