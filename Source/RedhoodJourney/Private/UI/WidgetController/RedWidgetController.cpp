// Copyright belong to Anas (Hanzo) Hatachi


#include "UI/WidgetController/RedWidgetController.h"
#include "Components/RedCombatComponent.h"
#include "Controllers/RedPlayerController.h"


void URedWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	RedCombatComponent = WCParams.CombatComponent;
}

void URedWidgetController::BroadcastInitialValues()
{
}

void URedWidgetController::BindCallbacksToDependencies()
{
}

ARedPlayerController* URedWidgetController::GetRedPlayerController()
{
	if (RedPlayerController == nullptr)
	{
		RedPlayerController = Cast<ARedPlayerController>(PlayerController);
	}
	return RedPlayerController;
}

URedCombatComponent* URedWidgetController::GetRedCombatComponent()
{
	if (IsValid(RedCombatComponent)) return RedCombatComponent;
	if (!IsValid(RedPlayerController))
	{
		RedPlayerController = GetRedPlayerController();
	}
	APawn* Pawn = RedPlayerController->GetPawn(); // or GetCharacter()
	if (!Pawn) return nullptr;

	RedCombatComponent = Pawn->FindComponentByClass<URedCombatComponent>();
	return RedCombatComponent;
}
