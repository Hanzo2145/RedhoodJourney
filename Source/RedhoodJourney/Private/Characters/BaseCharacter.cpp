// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/BaseCharacter.h"
#include "PaperZD/Public/PaperZDAnimationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZDAnimation");
}

void ABaseCharacter::SetCombatTarget_Implementation(AActor* CombatTarget)
{
}
