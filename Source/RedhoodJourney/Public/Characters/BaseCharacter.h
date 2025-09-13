/*Copyright belong to Anas (Hanzo) Hatachi*/

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
	virtual void AttackTrace_Implementation() override;
	virtual UPaperZDAnimationComponent* GetPaperZdAnimationComponent_Implementation() override {return PaperZDAnimation;}
	virtual void SetInoutEnabled_Implementation(const bool IsEnabled) override;
	/*ICombatInterface Functions/*/

	/*
	 * Functions
	 */
	
	UFUNCTION()
	virtual void HandleDeath(bool IsDead);

	/*
	 * DELEGATES
	 */

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathEventDispatcher;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UPaperZDAnimSequence> AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float Damage;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerController* PlayerController;
	
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
