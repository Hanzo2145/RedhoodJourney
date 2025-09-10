// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AttackTypes.h"
#include "Redhood.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperZdAnimationComponent;

/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API ARedhood : public ABaseCharacter
{
	GENERATED_BODY()

	ARedhood();
	
public:
	/*
	 * ICombat Interface Functions
	 */
	virtual bool GetIsAttacking_Implementation() override;
	virtual void SetAttackWindow_Implementation(bool Open) override;
	virtual void ResetCombatVariables_Implementation() override;
	virtual void ResetLightAttacking_Implementation() override;
	virtual void ResetHeavyAttacking_Implementation() override;
	virtual void LightAttack_Implementation() override;
	virtual void HeavyAttack_Implementation() override;
	virtual void SetIsLightAttack_Implementation(bool InLightAttack) override;
	virtual bool GetIsLightAttacking_Implementation() override;
	/*
	 * Ends
	 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath(bool IsDead) override;
	void RedhoodAttack(TArray<FAttack> AttackInfo);
	void HandleAttackReset(TArray<FAttack> AttackInfo, int32 InAttackCount);
	void IncrementAttackCount();

	
	/*
	 * Variables Declarations
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttack> LightAttacks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttack> HeavyAttacks;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	bool bAttackWindow = false;
	bool bComboActivated = false;
	bool bAttacking = false;
	int32 AttackCount = 0;
	bool bIsLightAttacking = false;
	
	void PlayFirstAttack(const TArray<FAttack> AttackAnimData);
	void PlayComboAttack(const TArray<FAttack> AttackAnimationData, int32 InAttackCount);
};
