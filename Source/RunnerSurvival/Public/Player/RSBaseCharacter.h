// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "RSBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UCameraComponent;
class UGameplayAbility;
class UPrimitiveComponent;
class USphereComponent;
class USpringArmComponent;
class UWidgetComponent;

class URSHealthComponent;
class URSAttributeSet;

UCLASS()
class RUNNERSURVIVAL_API ARSBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARSBaseCharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	URSAttributeSet* AttributeSet;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void SetWantsRun(bool bNewWantsToRun);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayAbility> MeleeAttackAbility;

	//Change Ability Level with Tag
	UFUNCTION(BlueprintCallable, Category = "GASGameplayAbility")
	void ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "GASGameplayAbility")
	int32 GetLevelAbilityByTag(FGameplayTagContainer TagContainer);
	
	void MeleeAttack();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	URSHealthComponent* HealthComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget = nullptr;

	virtual void BeginPlay() override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void OnDeath();

private:
	bool bMoveForward = false;
	bool bMoveRight = false;
	bool bWantsToRun = false;

	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckCameraOverlap();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void MuteSound();
};
