// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Player/RSBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/RSCharacterMovementComponent.h"
#include "Components/RSHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/RSGameModeBase.h"
#include <GameplayAbilities/Public/GameplayAbilitySpec.h>
#include "GAS/RSAttributeSet.h"
#include "PlayerStates/RSPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

ARSBaseCharacter::ARSBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<URSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeSet = CreateDefaultSubobject<URSAttributeSet>("AttributeSet");

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	check(IsValid(SpringArmComponent));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	check(IsValid(CameraComponent));
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	check(IsValid(CameraCollisionComponent));
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	HealthComponent = CreateDefaultSubobject<URSHealthComponent>("HealthComponent");

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	check(IsValid(OverheadWidget));
	OverheadWidget->SetupAttachment(RootComponent);
	OverheadWidget->SetVisibility(false); // SD : change for debug role
	bReplicates = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void ARSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();	

	check(CameraCollisionComponent);
	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetCapsuleComponent());
	check(GetWorld());

	HealthComponent->OnDeath.AddUObject(this, &ARSBaseCharacter::OnDeath); 
	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARSBaseCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ARSBaseCharacter::OnCameraCollisionEndOverlap);

	AquireAbility(MeleeAttackAbility);

	if (AbilitySystemComponent)
	{
		//Link Attribute Set to Ability System Component
		AttributeSet = const_cast<URSAttributeSet*>(AbilitySystemComponent->GetSet<URSAttributeSet>());
	}
}

void ARSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto* RSPlayerState = Cast<ARSPlayerState>(GetPlayerState());
	if (!IsValid(RSPlayerState))
	{
		return;
	}
	if (!IsValid(HealthComponent))
	{
		return;
	}
	if (!HealthComponent->IsDead())
	{
		RSPlayerState->SetLifeTime(GetWorld()->GetTimeSeconds() - RSPlayerState->GetTimeStartGame());
	}
}

void ARSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARSBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARSBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARSBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ARSBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("MuteSound", EInputEvent::IE_Pressed, this, &ARSBaseCharacter::MuteSound);

	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ARSBaseCharacter::MeleeAttack);
}

void ARSBaseCharacter::MoveForward(float Amount)
{
	bMoveForward = Amount != 0.0f;
	if (Amount == 0.0f)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ARSBaseCharacter::MoveRight(float Amount)
{
	bMoveRight = Amount != 0.0f;
	if (Amount == 0.0f)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Amount);
}

void ARSBaseCharacter::MuteSound()
{
	// Write logic for muting sounds in game
}

bool ARSBaseCharacter::IsRunning() const
{
	return bWantsToRun && (bMoveRight || bMoveForward) && !GetVelocity().IsZero();
}

void ARSBaseCharacter::SetWantsRun_Implementation(bool bNewWantsToRun)
{
	bWantsToRun = bNewWantsToRun;
}

void ARSBaseCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ARSBaseCharacter::OnCameraCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ARSBaseCharacter::CheckCameraOverlap()
{
	if (IsValid(GetMesh()) == false || IsValid(CameraCollisionComponent) == false)
	{
		return;
	}

	const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (auto* MeshChild : MeshChildren)
	{
		if (auto* MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild))
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}

float ARSBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ARSBaseCharacter::OnDeath_Implementation()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

	if (IsValid(GetCharacterMovement()) == false || IsValid(GetCapsuleComponent()) == false)
	{
		return;
	}
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (IsValid(GetMesh()) == false)
	{
		return;
	}
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

UAbilitySystemComponent* ARSBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARSBaseCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	if (HasAuthority() && AbilityToAquire)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ARSBaseCharacter::MeleeAttack()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	AbilitySystemComponent->TryActivateAbilityByClass(MeleeAttackAbility);
}

void ARSBaseCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewLevel)
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}
	TArray<FGameplayAbilitySpec*> MatchingAbility;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingAbility, true);
	for (FGameplayAbilitySpec* Spec : MatchingAbility)
	{
		Spec->Level = NewLevel;
	}
}

int32 ARSBaseCharacter::GetLevelAbilityByTag(FGameplayTagContainer TagContainer)
{
	if (!IsValid(AbilitySystemComponent))
	{
		return 0;
	}
	TArray<FGameplayAbilitySpec*> MatchingAbility;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingAbility, true);
	for (FGameplayAbilitySpec* Spec : MatchingAbility)
	{
		return Spec->Level;
	}
	return 0;
}