// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
//#include "ScalableFloat.h"
#include "Components/ActorComponent.h"
#include "RedCombatComponent.generated.h"

struct FAttack;
class UPaperZDAnimSequence;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, bool, Isdead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedSignature, float, NewValue);

UENUM(BlueprintType)
enum EAttributes
{
	EA_None UMETA(DisplayName = "None"),
	EA_Strength UMETA(DisplayName = "Strength"),
	EA_Agility UMETA(DisplayName = "Agility"),
	EA_Intiligent UMETA(DisplayName = "Intiligent"),
};

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EAttributes> Attribute = EA_None;

	UPROPERTY(EditDefaultsOnly)
	float Value = 5.f;

	/*UPROPERTY(EditDefaultsOnly)
	FScalableFloat UpgradeCost;*/
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDHOODJOURNEY_API URedCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URedCombatComponent();

	/*
	 * Functions
	 */
	void GetHit(float InDamage);
	void Heal(float InHeal);
	void AdjustStamina(float InStamina/*To Subtract add negative value*/);
	void AdjustMana(float InMana /*To Subtract add negative value*/);
	bool DoWeHaveStamina(TArray<FAttack> AtttackAnimData, int32 InAttackCount);
	float GetAttackCost(TArray<FAttack> AtttackAnimData, int32 InAttackCount);
	
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnValueChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnValueChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnValueChangedSignature OnStaminaChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UPaperZDAnimSequence> HitReactAnimation;

	/*
	 * Variables
	 */
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool IsDead = false;
	

private:

	/*
	 * Variables Declarations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Attributes")
	FAttributes Strength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Attributes")
	FAttributes Agility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Attributes")
	FAttributes Intiligent;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxMana;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float Mana;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxStamina;

	UPROPERTY()
	float MaxHealthMuli = 1.5f;
	
	UPROPERTY()
	float MaxManaMuli = 1.2f;

	UPROPERTY()
	float MaxStaminaMuli = 1.5f;

	UPROPERTY()
	float DamageMuli = 2.5f;

	UPROPERTY()
	float AgilityMuli = 3.f;
	
	


	/*
	 * FunctionsDeclarations
	 */
	void SetVitalAttributes();

	UFUNCTION(BlueprintPure, Category = "StateSetters")
	float GetFinalMaxHealth();

	UFUNCTION(BlueprintPure, Category = "StateSetters")
	float GetFinalMaxMana();

	UFUNCTION(BlueprintPure, Category = "StateSetters")
	float GetFinalMaxStamina();

	
};
