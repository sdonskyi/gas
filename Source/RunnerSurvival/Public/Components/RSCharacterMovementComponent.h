// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "RSCharacterMovementComponent.generated.h"

UCLASS()
class RUNNERSURVIVAL_API URSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	void SetRunModifier(float NewRunModifier);
	virtual float GetMaxSpeed() const override;

protected:	
	float RunModifier = 1.5f;
};
