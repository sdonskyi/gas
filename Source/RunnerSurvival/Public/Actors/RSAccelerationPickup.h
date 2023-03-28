// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Actors/RSBasePickup.h"
#include "Net/UnrealNetwork.h"
#include "RSAccelerationPickup.generated.h"

class ARSBaseCharacter;
class UWidgetComponent;

UCLASS()
class RUNNERSURVIVAL_API ARSAccelerationPickup : public ARSBasePickup
{
	GENERATED_BODY()

public:
	ARSAccelerationPickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerHandler")
	FTimerHandle PickupEffectTimerHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerHandler")
	FTimerHandle PickupReloadTimerHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* ReloadingTimerWidget = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_ActivatePickup)
	ARSBaseCharacter* PlayerActivatePickup = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	int32 PickupReloadDuration = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float AccelerationDuration = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration", meta = (ClampMin = "1.1", ClampMax = "10.0"))
	float SpeedUpCoefficient = 1.5f;

	virtual void BeginPlay() override;
	virtual void PickupOn() override;
	virtual bool GivePickupTo(ARSBaseCharacter* Player) override;

private:
	FTimerHandle ReloadingPickUpHandle;
	int32 Cooldown = 0;

	UFUNCTION()
	void OnRep_ActivatePickup();

	void DespellAcceleration(ARSBaseCharacter* Player);	
	void ReduceReloading();
	void SetTimerAndShow(int32 Time);

	bool ActivatePickupRealization(ARSBaseCharacter* Player);
};
