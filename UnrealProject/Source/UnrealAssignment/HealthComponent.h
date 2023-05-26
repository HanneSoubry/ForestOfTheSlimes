// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALASSIGNMENT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxSickness;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float m_CurrentHealth;
	float m_CurrentSickness;

	float m_SicknessIncrease;
	float m_SicknessDamage;

	float m_PoisonDamage;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// functions
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ResetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void InitializeParams(float newHealth, float newSickness);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void HealOverTime(float amount);
			// call this one every tick, as long as should heal

	UFUNCTION(BlueprintCallable, Category = "Health")
		void Heal(float amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateSickness(int amountSlimeNormal, int amountSlimePoison);

	// pure functions
	UFUNCTION(BlueprintCallable, Category = "Health")
		bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetSicknessPercentage() const;

	// blueprint overridable function
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
		void DoDamage(float amount, bool& isDead);


	// event dispatchers
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDeathSignature OnDeath;
};
