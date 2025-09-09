// Copyright belong to Anas (Hanzo) Hatachi


#include "Components/RedCombatComponent.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"

// Sets default values for this component's properties
URedCombatComponent::URedCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	MaxMana = 50.f;
	MaxStamina = 50.f;
	Health = MaxHealth;
	Mana = MaxMana;
	Stamina = MaxStamina;
	
}

// Called when the game starts
void URedCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetVitalAttributes();
}

void URedCombatComponent::GetHurt(float InDamage)
{
	Health = FMath::Clamp(Health - InDamage, 0, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	if (Health <= 0.f)
	{
		IsDead = true;
		OnDeath.Broadcast(IsDead);
	}
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwner());
	if (BaseCharacter)
	{
		BaseCharacter->GetPaperZDComponent()->GetAnimInstance()->PlayAnimationOverride(HitReactAnimation);
	}
}

void URedCombatComponent::Heal(float InHeal)
{
	Health = FMath::Clamp(Health + InHeal, 0, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void URedCombatComponent::AdjustStamina(float InStamina)
{
	Stamina = FMath::Clamp(Stamina - InStamina, 0, MaxStamina);
	OnStaminaChanged.Broadcast(Stamina);
}

void URedCombatComponent::AdjustMana(float InMana)
{
	Mana = FMath::Clamp(Mana - InMana, 0, MaxMana);
	OnManaChanged.Broadcast(Mana);
}

void URedCombatComponent::SetVitalAttributes()
{
	Health = GetFinalMaxHealth();
	Mana = GetFinalMaxMana();
	Stamina = GetFinalMaxStamina();
}

float URedCombatComponent::GetFinalMaxHealth()
{
	const float Value = Strength.Value * MaxHealthMuli;
	MaxHealth = MaxHealth + Value;
	return MaxHealth;
}

float URedCombatComponent::GetFinalMaxMana()
{
	const float Value = Intiligent.Value * MaxManaMuli;
	MaxMana = MaxMana + Value;
	return MaxMana;
}

float URedCombatComponent::GetFinalMaxStamina()
{
	const float Value = Agility.Value * MaxStaminaMuli;
	MaxStamina = MaxStamina + Value;
	return MaxStamina;
}


