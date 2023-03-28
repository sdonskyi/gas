// RunnerSurvival. All Rights Reserved. SDonskyi


#include "GAS/RSAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

URSAttributeSet::URSAttributeSet()
	: Health(100.f), MaxHealth(100.f)
{

}

float URSAttributeSet::GetManaPercent() const
{
	return GetMaxMana()!=0.f ? GetMana() / GetMaxMana() : 0.f;
}

void URSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("My Base HP: %f, My HP : %f"), Health.GetBaseValue(), Health.GetCurrentValue());
		HealthChangeDelegate.Broadcast(GetHealth(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		ManaChangeDelegate.Broadcast(GetMana(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetBaseAttackDamageAttribute())
	{
		SetBaseAttackDamage(FMath::Clamp(GetBaseAttackDamage(), 0.0f, 20.0f));
		BaseAttackDamageChangeDelegate.Broadcast(GetBaseAttackDamage(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetSpeedMultiplierAttribute())
	{
		SetSpeedMultiplier(FMath::Clamp(GetSpeedMultiplier(), 0.1f, 2.0f));
		SpeedMultiplierChangeDelegate.Broadcast(GetSpeedMultiplier(), Data.EffectSpec.StackCount);
	}
}

void URSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, BaseAttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URSAttributeSet, SpeedMultiplier, COND_None, REPNOTIFY_Always);
}

void URSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, Health, OldHealth);
}

void URSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, MaxHealth, OldMaxHealth);
}

void URSAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, Mana, OldMana);
}

void URSAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, MaxMana, OldMaxMana);
}

void URSAttributeSet::OnRep_BaseAttackDamage(const FGameplayAttributeData& OldBaseAttackDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, BaseAttackDamage, OldBaseAttackDamage);
}

void URSAttributeSet::OnRep_SpeedMultiplier(const FGameplayAttributeData& OldSpeedMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URSAttributeSet, SpeedMultiplier, OldSpeedMultiplier);
}
