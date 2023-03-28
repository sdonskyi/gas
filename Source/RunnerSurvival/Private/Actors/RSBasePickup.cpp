// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Actors/RSBasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/RSBaseCharacter.h"

ARSBasePickup::ARSBasePickup()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	check(IsValid(CollisionComponent))
	bReplicates = true;
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetIsReplicated(true);
	SetRootComponent(CollisionComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	check(IsValid(MeshComponent));
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetIsReplicated(true);
}

void ARSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	auto* BaseCharacter = Cast<ARSBaseCharacter>(OtherActor);
	if (IsValid(BaseCharacter))
	{
		GivePickupTo(BaseCharacter);
	}
}

void ARSBasePickup::PickupOn()
{
	PickupOnRealization();
	if (!HasAuthority())
	{
		PickupOnServer();
	}
}

void ARSBasePickup::PickupOff()
{
	PickupOffRealization();
	if (!HasAuthority())
	{
		PickupOffServer();
	}
}

bool ARSBasePickup::GivePickupTo(ARSBaseCharacter* Player)
{
	return false;
}

void ARSBasePickup::PickupOffServer_Implementation()
{
	PickupOff();
}

void ARSBasePickup::PickupOnServer_Implementation()
{
	PickupOn();
}

void ARSBasePickup::PickupOnRealization()
{
	if (IsValid(MeshComponent) == false || IsValid(CollisionComponent) == false)
	{
		return;
	}

	MeshComponent->SetVisibility(true, false);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ARSBasePickup::PickupOffRealization()
{
	if (IsValid(MeshComponent) == false || IsValid(CollisionComponent) == false)
	{
		return;
	}
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComponent->SetVisibility(false, false);
}
