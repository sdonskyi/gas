// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Components/RSCharacterMovementComponent.h"
#include "Player/RSBaseCharacter.h"
 
void URSCharacterMovementComponent::SetRunModifier(float NewRunModifier)
{
	if (NewRunModifier <= 1)
	{
		return;
	}
	RunModifier = NewRunModifier;
}

float URSCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ARSBaseCharacter* Player = Cast<ARSBaseCharacter>(GetPawnOwner());
	if (IsValid(Player) == false)
	{
		return MaxSpeed;
	}
	return Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
