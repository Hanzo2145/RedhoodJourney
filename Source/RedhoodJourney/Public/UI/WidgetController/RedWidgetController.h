// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "RedWidgetController.generated.h"
class ARedPlayerController;
class URedCombatComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()


	// the job of this Struct is to set the values of PlayerController, PlayerState, AbilitySystemComponenet, and AttributeSet
	FWidgetControllerParams() {}
	// in this Constructor we are setting these values
	FWidgetControllerParams(APlayerController* PC, URedCombatComponent* CComp)
	: PlayerController(PC), CombatComponent(CComp){}


	// we need to declare the Values and create Variable of the 4 types so can set them in the constructor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URedCombatComponent> CombatComponent = nullptr;
};
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API URedWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();;

protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<ARedPlayerController> RedPlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<URedCombatComponent> RedCombatComponent;

	ARedPlayerController* GetRedPlayerController();
	URedCombatComponent* GetRedCombatComponent();
};
