// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class URedUserWidget;
class UBehaviorTree;
class ARedAIController;
class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API AEnemyBase : public ABaseCharacter
{
	GENERATED_BODY()
public:
	/*ICombatInterface Functions*/
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual void Attack_Implementation() override;
	
	/*ICombatInterface Functions/*/
	
	AEnemyBase();
	virtual void PossessedBy(AController* NewController) override;
	virtual void HandleDeath(bool IsDead) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool EnemyIsDead = false;
	
protected:

	/*
	 * Functions Declarations
	 */
	virtual  void BeginPlay() override;

	/*
	 * Variables Declaration
	 */
	UPROPERTY(EditDefaultsOnly, Category= "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ARedAIController> RedAIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;
};
