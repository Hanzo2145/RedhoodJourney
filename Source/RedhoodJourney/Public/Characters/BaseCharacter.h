// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Interfaces/CombatInterface.h"
#include "BaseCharacter.generated.h"

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
	
	/*ICombatInterface Functions/*/

protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperZDAnimationComponent> PaperZDAnimation;
	
};
