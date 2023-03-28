// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Net/UnrealNetwork.h"
#include "RSHealthComponent.generated.h"

class AController;
class UDamageType;
class ARSBaseCharacter;

DECLARE_MULTICAST_DELEGATE(FOnDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChanged, URSHealthComponent*, RSHealthComponent, float, health, float, damage, const class UDamageType*, DamageType, class  AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNNERSURVIVAL_API URSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URSHealthComponent();

	FOnDeath OnDeath;

	ARSBaseCharacter* Owner = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Events")  
	FOnHealthChanged OnHealthChangedEvent;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

	bool IsHealthFull() const;
	bool TryToAddHealth(float HealthAmount);
	float GetHealth() const;

protected:
	UFUNCTION()
	void OnRep_Health();

	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
