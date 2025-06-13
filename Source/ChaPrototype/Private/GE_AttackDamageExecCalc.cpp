#include "GE_AttackDamageExecCalc.h"
#include "BaseAttributeSet.h" // 어트리뷰트 셋 헤더 포함
#include "AbilitySystemComponent.h"

UGE_AttackDamageExecCalc::UGE_AttackDamageExecCalc()
{
}

void UGE_AttackDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// 소스(공격자)와 타겟(피격자)의 ASC, AttributeSet 등을 가져옴
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const UBaseAttributeSet* SourceAttributes = Cast<UBaseAttributeSet>(SourceASC->GetAttributeSet(UBaseAttributeSet::StaticClass()));
	const UBaseAttributeSet* TargetAttributes = Cast<UBaseAttributeSet>(TargetASC->GetAttributeSet(UBaseAttributeSet::StaticClass()));

	// 필요한 어트리뷰트 값 가져오기
	const float SourceFirepower = SourceAttributes->GetFirepower();
	const float TargetArmor = TargetAttributes->GetArmor();

	// 데미지 계산 (예시: 화력 - 장갑)
	float Damage = FMath::Max<float>(SourceFirepower - TargetArmor, 0.0f);

	// 계산된 데미지를 타겟의 Health 속성에 적용하도록 설정
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBaseAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, -Damage));
}