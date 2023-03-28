// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "FirstGameInstanceSubsystem.generated.h"

UCLASS()
class FIRSTPLUGIN_API UFirstGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable, meta = (Category = "Lamp"))
	void SpawnLamp(FVector Location = FVector(0.0f, 0.0f, 0.0f));

private:
	TArray<AActor*> SpawnedActors;

};
