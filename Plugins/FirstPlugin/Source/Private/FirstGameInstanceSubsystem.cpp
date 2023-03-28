// RunnerSurvival. All Rights Reserved. SDonskyi


#include "FirstGameInstanceSubsystem.h"

void UFirstGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	SpawnLamp();
}

void UFirstGameInstanceSubsystem::SpawnLamp(FVector Location)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	
	UBlueprint* GeneratedBP = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/FirstPlugin/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight"), TEXT("LAMP")));
	
	if (IsValid(GeneratedBP) == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("BAD WORLD")));
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto* Actor = World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, Location, Rotation, SpawnParams);
	if (IsValid(Actor))
	{
		SpawnedActors.Add(Actor);
	}
}
