// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Actors/RSHealthPickup.h"
#include "Components/RSHealthComponent.h"
#include "Player/RSBaseCharacter.h"

bool ARSHealthPickup::GivePickupTo(ARSBaseCharacter* Player)
{
	if (IsValid(Player) == false)
	{
		return false;
	}

	auto* HealthComponent = Cast<URSHealthComponent>(Player->GetComponentByClass(URSHealthComponent::StaticClass()));

	if (IsValid(HealthComponent) == false)
	{
		return false;
	}

	if (HealthComponent->TryToAddHealth(HealthAmount))
	{
		PickupOff();
		OnHealingIsTaken.ExecuteIfBound();
		return true;
	}
	return false;
}
