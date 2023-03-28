// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Actors/RSJumpPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

ARSJumpPad::ARSJumpPad()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComponent);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Box");
	CollisionComp->SetupAttachment(MeshComponent);
}

void ARSJumpPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto* Character = Cast<ACharacter>(OtherActor);
	if (IsValid(Character) == false)
	{
		return;
	}

	Character->LaunchCharacter(FVector(0, 0, LaunchVelocityZ), false, true);
}