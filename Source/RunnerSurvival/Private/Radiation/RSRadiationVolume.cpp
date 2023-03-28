// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Radiation/RSRadiationVolume.h"

void ARSRadiationVolume::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetWorld()) == false)
	{
		return;
	}

	GetWorldTimerManager().SetTimer(DamageIncreaseTimerHandle, this, &ARSRadiationVolume::IncreaseDamage, DamageIncreaseTime, true, DamageIncreaseTime);
}

void ARSRadiationVolume::IncreaseDamage()
{
	DamagePerSec *= DamageIncreaseCoef;
}
