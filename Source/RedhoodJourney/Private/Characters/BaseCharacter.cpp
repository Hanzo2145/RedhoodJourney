// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/RedCombatComponent.h"
#include "PaperZD/Public/PaperZDAnimationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperZD/Public/PaperZDAnimInstance.h"

ABaseCharacter::ABaseCharacter()
{
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZDAnimation");
	CombatComponent = CreateDefaultSubobject<URedCombatComponent>("Combat Component"); 

	TraceStart = CreateDefaultSubobject<USceneComponent>("TraceStart");
	TraceStart->SetupAttachment(GetRootComponent());
	TraceEnd = CreateDefaultSubobject<USceneComponent>("TraceEnd");
	TraceEnd->SetupAttachment(GetRootComponent());

	TraceTarget.Empty();
	
}

void ABaseCharacter::AttackTrace_Implementation()
{
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	UKismetSystemLibrary::BoxTraceSingleForObjects(this,
		TraceStart->GetComponentLocation(),
		TraceEnd->GetComponentLocation(),
		TraceHalfSize,TraceOrientation,
		TraceTarget,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true);

	if (HitResult.bBlockingHit)
	{
		if (const ABaseCharacter* HitActor = Cast<ABaseCharacter>(HitResult.GetActor()))
		{
			HitActor->CombatComponent->GetHit(10.f);
		}
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CombatComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeath);
	PlayerController = Cast<APlayerController>(GetController());
}

void ABaseCharacter::HandleDeath(bool IsDead)
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetPaperZDComponent()->GetAnimInstance()->PlayAnimationOverride(DeathAnimation);
	GetPaperZDComponent()->GetAnimInstance()->StopAllAnimationOverrides();
	SetLifeSpan(LifeAfterDeath);
	OnDeathEventDispatcher.Broadcast(IsDead);
}

void ABaseCharacter::SetInputEnabled(bool InputEnabled) const
{
	if (IsValid(PlayerController))
	{
		if (InputEnabled)
		{
			PlayerController->EnableInput(PlayerController);
		}
		else
		{
			PlayerController->DisableInput(PlayerController);
		}
	}
}


