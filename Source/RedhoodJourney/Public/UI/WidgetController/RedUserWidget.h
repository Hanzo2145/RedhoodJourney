// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RedUserWidget.generated.h"



class URedWidgetController;
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API URedUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Function Declarations*/
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:

	/* when we start the game we want to set the controller of the widget*/
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};