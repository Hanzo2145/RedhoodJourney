// Copyright belong to Anas (Hanzo) Hatachi


#include "Components/RedCombatComponent.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Redhood.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/FloatingText/DamageNumber.h"

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

void URedCombatComponent::CreateDamageNumber(const float DamageNumber, const FVector& Location) const
{
	if (!DamageNumberClass) return;

	// Create widget properly
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	UDamageNumber* NumberWidget = CreateWidget<UDamageNumber>(PC, DamageNumberClass);
	if (!NumberWidget) return;

	// Set the damage text and color
	NumberWidget->SetNumber(DamageNumber, TextDamageColor);

	// Position it in screen space
	const FVector NewLocation = Location + FVector(0.f, 0.f, 75.f);
	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(PC, NewLocation, ScreenPosition))
	{
		NumberWidget->SetPositionInViewport(ScreenPosition, true);
	}

	// Add to viewport so it actually shows up
	NumberWidget->AddToViewport();
}

void URedCombatComponent::GetHit(float InDamage)
{
	const float FinalDamage = InDamage - GetFinalArmor() + 10.f;
	Health = FMath::Clamp(Health - FinalDamage, 0, MaxHealth);
	CreateDamageNumber(FinalDamage, GetOwner()->GetActorLocation());
	OnHealthChanged.Broadcast(Health);
	UE_LOG(LogTemp, Warning, TEXT("%s Current Health is: %f"), *UKismetSystemLibrary::GetObjectName(GetOwner()), Health);
	if (Health <= 0.f)
	{
		IsDead = true;
		OnDeath.Broadcast(IsDead);
		return;
	}
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwner());
	if (BaseCharacter)
	{
		ICombatInterface::Execute_GetPaperZdAnimationComponent(GetOwner())->GetAnimInstance()->PlayAnimationOverride(HitReactAnimation);
		ICombatInterface::Execute_SetInoutEnabled(GetOwner(), false);
	}
}

void URedCombatComponent::Heal(float InHeal)
{
	Health = FMath::Clamp(Health + InHeal, 0, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void URedCombatComponent::AdjustStamina(float InStamina)
{
	Stamina = FMath::Clamp(Stamina + InStamina, 0, MaxStamina);
	OnStaminaChanged.Broadcast(Stamina);
}

void URedCombatComponent::AdjustMana(float InMana)
{
	Mana = FMath::Clamp(Mana + InMana, 0, MaxMana);
	OnManaChanged.Broadcast(Mana);
}

bool URedCombatComponent::DoWeHaveStamina(TArray<FAttack> AttackAnimData, int32 InAttackCount) const
{
	const float AttackCost = GetAttackCost(AttackAnimData, InAttackCount);
	const bool ReturnValue = Stamina >= AttackCost;
	return ReturnValue;
}

float URedCombatComponent::GetAttackCost(TArray<FAttack> AttackAnimData, int32 InAttackCount) const
{
	const float StaminaCost = AttackAnimData[InAttackCount].StaminaCost;
	const float StrengthValue = Strength.Value * DamageMuli;
	const float AgilityValue = Agility.Value * AgilityMuli;
	const float SimiFinalValue = StaminaCost + StrengthValue;
	return SimiFinalValue - AgilityValue;
}

float URedCombatComponent::GetFinalAttackDamage(const float InDamage) const
{
	float Damage = Strength.Value * DamageMuli;
	float MaxDamage = FMath::Clamp(Damage + InDamage, 0, Damage + InDamage);
	return MaxDamage;
}

float URedCombatComponent::GetFinalArmor() const
{
	float ArmorFromAgility = Agility.Value * ArmorMuli;
	return Armor + ArmorFromAgility;
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
	OnMaxHealthChanged.Broadcast(MaxHealth);
	return MaxHealth;
}

float URedCombatComponent::GetFinalMaxMana()
{
	const float Value = Intiligent.Value * MaxManaMuli;
	MaxMana = MaxMana + Value;
	OnMaxManaChanged.Broadcast(MaxMana);
	return MaxMana;
}

float URedCombatComponent::GetFinalMaxStamina()
{
	const float Value = Agility.Value * MaxStaminaMuli;
	MaxStamina = MaxStamina + Value;
	OnMaxStaminaChanged.Broadcast(MaxStamina);
	return MaxStamina;
}


