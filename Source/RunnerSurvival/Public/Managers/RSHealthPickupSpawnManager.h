// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Managers/RSBaseManager.h"
#include "GameFramework/Actor.h"
#include "RSHealthPickupSpawnManager.generated.h"

class ARSHealthPickup;

UCLASS()
class RUNNERSURVIVAL_API ARSHealthPickupSpawnManager : public ARSBaseManager
{
	GENERATED_BODY()
	
public:
	ARSHealthPickupSpawnManager();

protected:
	UPROPERTY()
	TArray<AActor*> HealthPickups;

	virtual void BeginPlay() override;

private:
	const float DelayInitHealthPickups = 10.f;
	int32 IndexActiveHealthPickup = -1;

	void InitHealthPickups();
	void RandomHealingPickUpSwitchOn();	
	int GetRandomIndexArrayExceptIndexValue(const TArray<AActor*>& Array, const int32& ExceptedIndex);
};
