// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackTypes.h"
#include "CombatInterface.generated.h"

class UPaperZDAnimationComponent;
class UPaperZDAnimSequence;

class ABaseCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REDHOODJOURNEY_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AttackTrace();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsAttacking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetLightAttacking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetHeavyAttacking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LightAttack();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HeavyAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAttackWindow(bool Open);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetCombatVariables();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsLightAttack(bool InLightAttack);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsLightAttacking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimationComponent* GetPaperZdAnimationComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetInoutEnabled(const bool IsEnabled);
};
