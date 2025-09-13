// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/RedWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedSignature, float, NewValue);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class REDHOODJOURNEY_API UOverlayWidgetController : public URedWidgetController
{
	GENERATED_BODY()
public:
	/*
	 * Function Declarations
	 */
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnMaxManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnStaminaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "RED|Attribute")
	FOnValueChangedSignature OnMaxStaminaChanged;

protected:
	UFUNCTION() void HandleHealth(float NewValue);
	UFUNCTION() void HandleMaxHealth(float NewValue);
	UFUNCTION() void HandleMana(float NewValue);
	UFUNCTION() void HandleMaxMana(float NewValue);
	UFUNCTION() void HandleStamina(float NewValue);
	UFUNCTION() void HandleMaxStamina(float NewValue);
};
