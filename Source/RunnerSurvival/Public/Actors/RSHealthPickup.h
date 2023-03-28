// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Actors/RSBasePickup.h"
#include "RSHealthPickup.generated.h"

class ARSBaseCharacter;

UCLASS()
class RUNNERSURVIVAL_API ARSHealthPickup : public ARSBasePickup
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE(FHealingIsTaken)
	FHealingIsTaken OnHealingIsTaken;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;

private:
	virtual bool GivePickupTo(ARSBaseCharacter* Player) override;
};
