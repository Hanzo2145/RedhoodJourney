// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
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
	virtual void Attack_Implementation() override;
	/*
	 * Ends
	 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath(bool IsDead) override;


private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
};
