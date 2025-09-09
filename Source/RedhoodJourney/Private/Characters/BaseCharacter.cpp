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

void ABaseCharacter::SetCombatTarget_Implementation(AActor* CombatTarget)
{
	
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
		EDrawDebugTrace::ForDuration,
		HitResult,
		true);

	if (HitResult.bBlockingHit)
	{
		const ABaseCharacter* HitActor = Cast<ABaseCharacter>(HitResult.GetActor());
		if (HitActor)
		{
			HitActor->CombatComponent->GetHurt(10.f);
		}
	}
}

void ABaseCharacter::Attack_Implementation()
{
	
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CombatComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeath);
}

void ABaseCharacter::HandleDeath(bool IsDead)
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PaperZDAnimation->GetAnimInstance()->PlayAnimationOverride(DeathAnimation);
	SetLifeSpan(LifeAfterDeath);
	OnDeathEventDispatcher.Broadcast(IsDead);
}


