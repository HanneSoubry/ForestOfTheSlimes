// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 100.f;
	m_CurrentHealth = MaxHealth;

	MaxSickness = 10.f;
	m_CurrentSickness = 0.f;

	m_SicknessIncrease = 1.f;
	m_SicknessDamage = 2.f;

	m_PoisonDamage = 2.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ResetHealth()
{
	m_CurrentHealth = MaxHealth;
}

float UHealthComponent::GetHealthPercentage() const
{
	return m_CurrentHealth / MaxHealth;
}

float UHealthComponent::GetSicknessPercentage() const
{
	return m_CurrentSickness / MaxSickness;
}

bool UHealthComponent::IsDead() const
{
	if (GetHealthPercentage() <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UHealthComponent::DoDamage_Implementation(float amount, bool& isDead)
{
	float originalHealth = m_CurrentHealth;

	m_CurrentHealth -= amount;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth, 0.0f, MaxHealth);

	isDead = IsDead();
	if (isDead && originalHealth > m_CurrentHealth)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::InitializeParams(float newHealth, float newSickness)
{
	MaxHealth = newHealth;
	MaxSickness = newSickness;

	ResetHealth();
}

void UHealthComponent::HealOverTime(float amount)
{
	m_CurrentHealth += amount * FApp::GetDeltaTime();

	// clamp value
	if (m_CurrentHealth > MaxHealth)
		m_CurrentHealth = MaxHealth;
}

void UHealthComponent::Heal(float amount)
{
	m_CurrentHealth += amount;

	// clamp value
	if (m_CurrentHealth > MaxHealth)
		m_CurrentHealth = MaxHealth;
}

void UHealthComponent::UpdateSickness(int amountSlimeNormal, int amountSlimePoison)
{
	double deltaTime{ FApp::GetDeltaTime() };

	// increase sickness
	int totalSlime{ amountSlimeNormal + amountSlimePoison };
	m_CurrentSickness += totalSlime * m_SicknessIncrease * deltaTime;

	// clamp value
	if (m_CurrentSickness > MaxSickness)
		m_CurrentSickness = MaxSickness;

	bool isDead{};
	if (amountSlimePoison != 0)
	{
		// if poison, do damage
		DoDamage(amountSlimePoison * m_PoisonDamage * deltaTime, isDead);
	}

	if (!isDead && m_CurrentSickness >= MaxSickness && totalSlime > 0)
	{
		// if sick, do damage
		DoDamage(totalSlime * m_SicknessDamage * deltaTime, isDead);
	}
}
