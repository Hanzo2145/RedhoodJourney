// Copyright belong to Anas (Hanzo) Hatachi


#include "Controllers/RedPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/CombatInterface.h"
#include "Controllers/RedEnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ARedPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ARedPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARedPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* RedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	RedInput->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ARedPlayerController::Move);
	RedInput->BindAction(JumpInput, ETriggerEvent::Started, this, &ARedPlayerController::Jump);
	RedInput->BindAction(LightAttackInput, ETriggerEvent::Started, this, &ARedPlayerController::LightAttack);
	RedInput->BindAction(HeavyAttackInput, ETriggerEvent::Started, this, &ARedPlayerController::HeavyAttack);
	RedInput->BindAction(DodgeInput, ETriggerEvent::Started, this, &ARedPlayerController::Dodge);
	
}

void ARedPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!ICombatInterface::Execute_GetIsAttacking(GetCharacter()))
 	{
		const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

		const FVector ForwardDirection = FVector::ForwardVector;
		const FVector PlayerCurrentAcceleration = GetCharacter()->GetCharacterMovement()->GetCurrentAcceleration();
		
		if (PlayerCurrentAcceleration.X < 0)
		{
			SetControlRotation(FRotator(0.f, 180.f, 0.f));
		}
		else if (PlayerCurrentAcceleration.X > 0)
		{
			SetControlRotation(FRotator(0.f, 0.f, 0.f));
		}
	
		if (APawn* ControlledPawn = GetPawn())
		{
			ControlledPawn->AddMovementInput(ForwardDirection, FMath::RoundToInt32(InputAxisVector.X));
		}
	}
}

void ARedPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (!ICombatInterface::Execute_GetIsAttacking(GetCharacter()))
	{
		GetCharacter()->Jump();
	}
}

void ARedPlayerController::LightAttack(const FInputActionValue& InputActionValue)
{
	ICombatInterface::Execute_SetIsLightAttack(GetCharacter(), true);
	ICombatInterface::Execute_LightAttack(GetCharacter());
}

void ARedPlayerController::HeavyAttack(const FInputActionValue& InputActionValue)
{
	ICombatInterface::Execute_SetIsLightAttack(GetCharacter(), false);
	ICombatInterface::Execute_HeavyAttack(GetCharacter());
}

void ARedPlayerController::Dodge(const FInputActionValue& InputActionValue)
{
	
}
