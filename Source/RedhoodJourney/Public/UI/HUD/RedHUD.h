// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RedHUD.generated.h"

class UOverlayWidgetController;
class URedCombatComponent;
struct FWidgetControllerParams;
class URedUserWidget;
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API ARedHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, URedCombatComponent* CombatComponent);


private:
	UPROPERTY()
	TObjectPtr<URedUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<URedUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};