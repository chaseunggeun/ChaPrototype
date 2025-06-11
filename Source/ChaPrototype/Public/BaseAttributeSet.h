// BaseAttributeSet.h

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CHAPROTOTYPE_API UBaseAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UBaseAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // 속성 변경 처리
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    
    //== 1차 속성 (Primary Attributes) ==//
    UPROPERTY(BlueprintReadOnly, Category = "Primary", ReplicatedUsing = OnRep_Attack)
    FGameplayAttributeData Attack;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Attack);

    UPROPERTY(BlueprintReadOnly, Category = "Primary", ReplicatedUsing = OnRep_Defense)
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Defense);
    
    UPROPERTY(BlueprintReadOnly, Category = "Primary", ReplicatedUsing = OnRep_Durability)
    FGameplayAttributeData Durability;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Durability);

    UPROPERTY(BlueprintReadOnly, Category = "Primary", ReplicatedUsing = OnRep_Speed)
    FGameplayAttributeData Speed;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Speed);

    //== 2차 속성 (Secondary Attributes) ==//
    UPROPERTY(BlueprintReadOnly, Category = "Secondary", ReplicatedUsing = OnRep_Firepower)
    FGameplayAttributeData Firepower; // 화력
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Firepower);

    UPROPERTY(BlueprintReadOnly, Category = "Secondary", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor; // 장갑
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Armor);
    
    UPROPERTY(BlueprintReadOnly, Category = "Secondary", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth; // 최대체력
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);
    
    UPROPERTY(BlueprintReadOnly, Category = "Secondary", ReplicatedUsing = OnRep_AttackSpeed)
    FGameplayAttributeData AttackSpeed; // 공격속도
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackSpeed);
    
    UPROPERTY(BlueprintReadOnly, Category = "Secondary", ReplicatedUsing = OnRep_MovementSpeed)
    FGameplayAttributeData MovementSpeed; // 이동속도
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MovementSpeed);

    //== 현재 속성 (Vital Attributes) ==//
    UPROPERTY(BlueprintReadOnly, Category = "Vital", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health; // 체력
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);
    
protected:
    // 리플리케이션 콜백 함수들
    UFUNCTION() virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);
    UFUNCTION() virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);
    UFUNCTION() virtual void OnRep_Durability(const FGameplayAttributeData& OldDurability);
    UFUNCTION() virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);
    
    UFUNCTION() virtual void OnRep_Firepower(const FGameplayAttributeData& OldFirepower);
    UFUNCTION() virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);
    UFUNCTION() virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
    UFUNCTION() virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);
    UFUNCTION() virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
    
    UFUNCTION() virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
};
