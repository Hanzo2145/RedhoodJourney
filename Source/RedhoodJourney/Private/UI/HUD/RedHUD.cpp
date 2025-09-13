// Copyright belong to Anas (Hanzo) Hatachi


#include "UI/HUD/RedHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/RedUserWidget.h"


UOverlayWidgetController* ARedHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return  OverlayWidgetController;
}

void ARedHUD::InitOverlay(APlayerController* PC, URedCombatComponent* CombatComponent)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_RedHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_RedHUD"));
	
	OverlayWidget = CreateWidget<URedUserWidget>(PC, OverlayWidgetClass);
	const FWidgetControllerParams WidgetControllerParams(PC, CombatComponent);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}
