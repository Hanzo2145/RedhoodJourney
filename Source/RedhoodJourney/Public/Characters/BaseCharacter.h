// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Interfaces/CombatInterface.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, bool, IsDead);

class UPaperZDAnimSequence;
class URedCombatComponent;
class UPaperZDAnimationComponent;
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API ABaseCharacter : public APaperCharacter,  public ICombatInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	/*ICombatInterface Functions*/
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual void AttackTrace_Implementation() override;
	virtual void Attack_Implementation() override;
	/*ICombatInterface Functions/*/

	/*
	 * Functions
	 */
	FORCEINLINE UPaperZDAnimationComponent* GetPaperZDComponent() { return PaperZDAnimation; }
	
	UFUNCTION()
	virtual void HandleDeath(bool IsDead);

	/*
	 * DELEGATES
	 */

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathEventDispatcher;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UPaperZDAnimSequence> AttackAnimation;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperZDAnimationComponent> PaperZDAnimation;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URedCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> TraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> TraceEnd;

	UPROPERTY(EditAnywhere, Category="Combat")
	FVector TraceHalfSize = FVector(20.0f, 20.0f, 20.0f);

	UPROPERTY(EditAnywhere, Category="Combat")
	FRotator TraceOrientation;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceTarget;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float LifeAfterDeath = 3.f;
	/*
	 * Animations
	 */
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UPaperZDAnimSequence> DeathAnimation;
};
