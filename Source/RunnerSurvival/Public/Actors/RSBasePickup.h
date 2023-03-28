// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "RSBasePickup.generated.h"

class ARSBaseCharacter;
class USphereComponent;

UCLASS()
class RUNNERSURVIVAL_API ARSBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSBasePickup();

	virtual void PickupOn();
	virtual void PickupOff();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent = nullptr;

private:
	UFUNCTION(Server, Reliable)
	virtual void PickupOnServer();
	UFUNCTION(Server, Reliable)
	virtual void PickupOffServer();

	virtual void PickupOnRealization();
	virtual void PickupOffRealization();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual bool GivePickupTo(ARSBaseCharacter* Player);
};
