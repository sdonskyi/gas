// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Components/RSHealthComponent.h"
#include "Player/RSBaseCharacter.h"
#include "GameStates/RSGameStateBase.h"
#include "GAS/RSAttributeSet.h"
#include "GAS/RSAttributeSet.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

URSHealthComponent::URSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void URSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//check(AttributeSet);
	//check(AttributeSet->Health.GetBaseValue());
	//check(MaxHealth > 0);
	check(GetWorld());
	//SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (IsValid(ComponentOwner))
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &URSHealthComponent::OnTakeAnyDamage);

		Owner = Cast<ARSBaseCharacter>(ComponentOwner);
		check(Owner);
	}

	ARSGameStateBase* RSGameStateBase = GetWorld()->GetGameState<ARSGameStateBase>();
	if (IsValid(RSGameStateBase))
	{
		// SD : OnDeath.AddUObject(RSGameStateBase, &ARSGameStateBase::EndGame);
	}	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RSGameStateBase invalid"));
	}
	SetIsReplicated(true);
}

void URSHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AActor* ComponentOwner = GetOwner();
	if (IsValid(ComponentOwner))
	{
		ComponentOwner->OnTakeAnyDamage.RemoveDynamic(this, &URSHealthComponent::OnTakeAnyDamage);
	}
}

float URSHealthComponent::GetHealthPercent() const 
{
	//return MaxHealth>0 ? Health / MaxHealth : 0;
	return Owner->AttributeSet->GetHealth() > 0 ? Owner->AttributeSet->GetHealth() / Owner->AttributeSet->GetMaxHealth() : 0;
}

float URSHealthComponent::GetHealth() const 
{
	//return Health;
	return Owner->AttributeSet->GetHealth();
}

bool URSHealthComponent::IsDead() const
{
	//return FMath::IsNearlyZero(Health); 
	return FMath::IsNearlyZero(Owner->AttributeSet->GetHealth());
}

void URSHealthComponent::SetHealth(float NewHealth)
{
	//Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	Owner->AttributeSet->SetHealth(FMath::Clamp(NewHealth, 0.0f, Owner->AttributeSet->GetMaxHealth()));
}

bool URSHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsHealthFull())
	{
		return false;
	}

	//SetHealth(Health + HealthAmount);
	SetHealth(Owner->AttributeSet->GetHealth() + HealthAmount);
	return true;
}

bool URSHealthComponent::IsHealthFull() const
{
	//return FMath::IsNearlyEqual(Health, MaxHealth);
	return FMath::IsNearlyEqual(Owner->AttributeSet->GetHealth(), Owner->AttributeSet->GetMaxHealth());
}

void URSHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	//Health = FMath::Clamp(Health- Damage, 0.0f, MaxHealth);
	SetHealth(Owner->AttributeSet->GetHealth() - Damage);
	OnHealthChangedEvent.Broadcast(this, Owner->AttributeSet->GetHealth(), Damage, DamageType, InstigatedBy, DamageCauser);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}	
}

/*
void URSHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(URSHealthComponent, Health);
	DOREPLIFETIME(URSHealthComponent, Owner->AttributeSet);
}*/

void URSHealthComponent::OnRep_Health()
{
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}