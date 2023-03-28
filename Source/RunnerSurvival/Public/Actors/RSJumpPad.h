// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/Actor.h"
#include "RSJumpPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class RUNNERSURVIVAL_API ARSJumpPad : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSJumpPad();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JumpPad")
	float LaunchVelocityZ = 1;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
