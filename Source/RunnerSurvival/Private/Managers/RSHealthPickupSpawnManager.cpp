// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Managers/RSHealthPickupSpawnManager.h"
#include "Actors/RSHealthPickup.h"
#include "Kismet/GameplayStatics.h"

ARSHealthPickupSpawnManager::ARSHealthPickupSpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARSHealthPickupSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(GetWorld()))
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ARSHealthPickupSpawnManager::InitHealthPickups, DelayInitHealthPickups);
	}
}

int32 ARSHealthPickupSpawnManager::GetRandomIndexArrayExceptIndexValue(const TArray<AActor*>& Array, const int32& ExceptedIndex)
{
	int32 RandomIndex = FMath::RandRange(0, Array.Num() - 2); // Max index - 1
	if (RandomIndex >= ExceptedIndex)
	{
		++RandomIndex;
	}
	return RandomIndex;
}

void ARSHealthPickupSpawnManager::RandomHealingPickUpSwitchOn()
{
	if (HealthPickups.Num() == 0 || HealthPickups.Num()==1)
	{
		return;
	}

	int32 RandomIndex = GetRandomIndexArrayExceptIndexValue(HealthPickups, IndexActiveHealthPickup);
	AActor* RandomPickUpBaseActor = HealthPickups[RandomIndex];
	ARSHealthPickup* HealthPickup = Cast<ARSHealthPickup>(RandomPickUpBaseActor);
	if (IsValid(HealthPickup))
	{
		IndexActiveHealthPickup = RandomIndex;
		HealthPickup->PickupOn();
	}
}

void ARSHealthPickupSpawnManager::InitHealthPickups()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSHealthPickup::StaticClass(), HealthPickups);
	for (AActor* PickupActor : HealthPickups)
	{
		if (ARSHealthPickup* HealthPickup = Cast<ARSHealthPickup>(PickupActor))
		{
			HealthPickup->OnHealingIsTaken.BindUObject(this, &ARSHealthPickupSpawnManager::RandomHealingPickUpSwitchOn);
			HealthPickup->PickupOff();
		}
	}
	IndexActiveHealthPickup = -1;
	RandomHealingPickUpSwitchOn();
}