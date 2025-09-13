// Copyright belong to Anas (Hanzo) Hatachi


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Components/RedCombatComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetRedCombatComponent()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetRedCombatComponent()->GetMaxHealth());
	OnManaChanged.Broadcast(GetRedCombatComponent()->GetMana());
	OnMaxManaChanged.Broadcast(GetRedCombatComponent()->GetMaxMana());
	OnStaminaChanged.Broadcast(GetRedCombatComponent()->GetStamina());
	OnMaxStaminaChanged.Broadcast(GetRedCombatComponent()->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	URedCombatComponent* RedCC = GetRedCombatComponent();
	if (!RedCC) return;

	RedCC->OnHealthChanged.AddDynamic(this, &UOverlayWidgetController::HandleHealth);
	RedCC->OnMaxHealthChanged.AddDynamic(this, &UOverlayWidgetController::HandleMaxHealth);
	RedCC->OnManaChanged.AddDynamic(this, &UOverlayWidgetController::HandleMana);
	RedCC->OnMaxManaChanged.AddDynamic(this, &UOverlayWidgetController::HandleMaxMana);
	RedCC->OnStaminaChanged.AddDynamic(this, &UOverlayWidgetController::HandleStamina);
	RedCC->OnMaxStaminaChanged.AddDynamic(this, &UOverlayWidgetController::HandleMaxStamina);
}

void UOverlayWidgetController::HandleHealth(float V)
{
	OnHealthChanged.Broadcast(V);
}
void UOverlayWidgetController::HandleMaxHealth(float V)
{
	OnMaxHealthChanged.Broadcast(V);
}
void UOverlayWidgetController::HandleMana(float V)
{
	OnManaChanged.Broadcast(V);
}
void UOverlayWidgetController::HandleMaxMana(float V)
{
	OnMaxManaChanged.Broadcast(V);
}
void UOverlayWidgetController::HandleStamina(float V)
{
	OnStaminaChanged.Broadcast(V);
}
void UOverlayWidgetController::HandleMaxStamina(float V)
{
	OnMaxStaminaChanged.Broadcast(V);
}
