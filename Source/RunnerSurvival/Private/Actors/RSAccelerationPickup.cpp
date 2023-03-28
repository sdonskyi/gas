// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Actors/RSAccelerationPickup.h"
#include "Components/RSCharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/RSBaseCharacter.h"
#include "UI/RSReloadingWidget.h"

ARSAccelerationPickup::ARSAccelerationPickup()
{
	ReloadingTimerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ReloadingWidget"));	
	if (IsValid(ReloadingTimerWidget) == false)
	{
		return;
	}
	ReloadingTimerWidget->SetupAttachment(RootComponent);
	ReloadingTimerWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ReloadingTimerWidget->SetDrawAtDesiredSize(true);
}

void ARSAccelerationPickup::BeginPlay()
{
	Super::BeginPlay();

	check(ReloadingTimerWidget);
}

void ARSAccelerationPickup::OnRep_ActivatePickup()
{
	if (IsValid(PlayerActivatePickup))
	{
		ActivatePickupRealization(PlayerActivatePickup);
	}
}

void ARSAccelerationPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARSAccelerationPickup, PlayerActivatePickup);
}

bool ARSAccelerationPickup::ActivatePickupRealization(ARSBaseCharacter* Player)
{
	if (IsValid(GetWorld()) == false)
	{
		return false;
	}
	
	if (IsValid(Player) == false)
	{
		return false;
	}

	auto* MovementComponent = Cast<URSCharacterMovementComponent>(Player->GetComponentByClass(URSCharacterMovementComponent::StaticClass()));

	if (IsValid(MovementComponent) == false)
	{
		return false;
	}

	FTimerDelegate PickupEffectDelegate = FTimerDelegate::CreateUObject(this, &ARSAccelerationPickup::DespellAcceleration, Player);
	GetWorldTimerManager().SetTimer(PickupEffectTimerHandler, PickupEffectDelegate, AccelerationDuration, false);

	MovementComponent->SetRunModifier(SpeedUpCoefficient);
	Player->SetWantsRun(true);

	Cooldown = PickupReloadDuration;

	SetTimerAndShow(Cooldown);
	GetWorld()->GetTimerManager().SetTimer(ReloadingPickUpHandle, this, &ARSAccelerationPickup::ReduceReloading, 1, true, 1);

	return true;
}

bool ARSAccelerationPickup::GivePickupTo(ARSBaseCharacter* Player)
{
	if (IsValid(Player) == false)
	{
		return false;
	}

	bool bResult = ActivatePickupRealization(Player);
	if (bResult)
	{
		PlayerActivatePickup = Player;
		PickupOff();
	}
	return bResult;
}

void ARSAccelerationPickup::DespellAcceleration(ARSBaseCharacter* Player)
{
	if (IsValid(Player))
	{
		Player->SetWantsRun(false);
	}
}

void ARSAccelerationPickup::ReduceReloading()
{
	if (IsValid(ReloadingTimerWidget) == false || IsValid(GetWorld()) == false )
	{
		return;
	}
	if (PlayerActivatePickup)
	{
		PlayerActivatePickup = nullptr;
	}
	--Cooldown;
	auto* ReloadingWidget = Cast<URSReloadingWidget>(ReloadingTimerWidget->GetUserWidgetObject());
	if (IsValid(ReloadingWidget) == false)
	{
		return;
	}
	ReloadingWidget->SetTimer(Cooldown);
	if (Cooldown == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadingPickUpHandle);		
		PickupOn();
	}
}

void ARSAccelerationPickup::SetTimerAndShow(int32 Time)
{
	if (IsValid(ReloadingTimerWidget) == false)
	{
		return;
	}
	ReloadingTimerWidget->SetVisibility(true, true);
	auto* ReloadingWidget = Cast<URSReloadingWidget>(ReloadingTimerWidget->GetUserWidgetObject());
	if (IsValid(ReloadingWidget) == false)
	{
		return;
	}
	ReloadingWidget->SetTimer(Time);
	ReloadingWidget->SetTimerVisible(true);
}

void ARSAccelerationPickup::PickupOn()
{
	Super::PickupOn();
	if (!Cooldown)
	{
		auto* ReloadingWidget = Cast<URSReloadingWidget>(ReloadingTimerWidget->GetUserWidgetObject());
		if (IsValid(ReloadingWidget) == false)
		{
			return;
		}
		ReloadingWidget->SetTimerVisible(false);
	}
}