// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/PainCausingVolume.h"
#include "RSRadiationVolume.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSRadiationVolume : public APainCausingVolume
{
	GENERATED_BODY()	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PainCausingVolume")
	float DamageIncreaseCoef = 1.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PainCausingVolume")
	float DamageIncreaseTime = 5.0f;

	virtual void BeginPlay() override;

private:
	FTimerHandle DamageIncreaseTimerHandle;

	void IncreaseDamage();
};
