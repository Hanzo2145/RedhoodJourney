// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/Redhood.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/RedCombatComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ARedhood::ARedhood()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

bool ARedhood::GetIsAttacking_Implementation()
{
	return bAttacking;
}

void ARedhood::SetAttackWindow_Implementation(bool Open)
{
	bAttackWindow = Open;
}

void ARedhood::ResetCombatVariables_Implementation()
{
	SetInputEnabled(true);
	bAttacking = false;
	bAttackWindow = false;
	bComboActivated = false;
	AttackCount = 0;
}

void ARedhood::ResetLightAttacking_Implementation()
{
	HandleAttackReset(LightAttacks, AttackCount);
}

void ARedhood::ResetHeavyAttacking_Implementation()
{
	HandleAttackReset(HeavyAttacks, AttackCount);
}

void ARedhood::LightAttack_Implementation()
{
	RedhoodAttack(LightAttacks);
}

void ARedhood::HeavyAttack_Implementation()
{
	RedhoodAttack(HeavyAttacks);
}

void ARedhood::SetIsLightAttack_Implementation(bool InLightAttack)
{
	bIsLightAttacking = InLightAttack;
}

bool ARedhood::GetIsLightAttacking_Implementation()
{
	return bIsLightAttacking;
}

void ARedhood::BeginPlay()
{
	Super::BeginPlay();
}

void ARedhood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARedhood::HandleDeath(bool IsDead)
{
	Super::HandleDeath(IsDead);
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(LevelName));
}

void ARedhood::RedhoodAttack(TArray<FAttack> AttackInfo)
{
	if (bAttackWindow)
	{
		bComboActivated = true;
	}
	else
	{
		PlayFirstAttack(AttackInfo);
	}	
}

void ARedhood::HandleAttackReset(TArray<FAttack> AttackInfo, int32 InAttackCount)
{
	if (bComboActivated)
	{
		int32 AttackAnimDataLength = AttackInfo.Num() - 1;
		IncrementAttackCount();
		const bool IsAttackCountHigher = AttackCount > AttackAnimDataLength;
		if (IsAttackCountHigher)
		{
			AttackCount = 0;
			bAttacking = false;
			bComboActivated = false;
		}
		else
		{
			PlayComboAttack(AttackInfo, AttackCount);
			bComboActivated = false;
		}
	}
	else
	{
		bAttacking = false;
		AttackCount = 0;
	}
}

void ARedhood::IncrementAttackCount()
{
	AttackCount ++;
}

void ARedhood::PlayFirstAttack(const TArray<FAttack> AttackAnimData)
{
	if (!bAttacking)
	{
		bAttacking = true;
		PlayComboAttack(AttackAnimData, 0);
	}
}

void ARedhood::PlayComboAttack(const TArray<FAttack> AttackAnimationData, int32 InAttackCount)
{
	bool DoesHaveStamina = CombatComponent->DoWeHaveStamina(AttackAnimationData, InAttackCount);
	FAttack Data = AttackAnimationData[AttackCount];
	if (DoesHaveStamina)
	{
		Damage = Data.AttackDamage;
		GetPaperZDComponent()->GetAnimInstance()->PlayAnimationOverride(Data.AttackAnimation);
		TraceHalfSize = Data.BoxTraceExtent;
		TraceStart->SetRelativeLocation(Data.BoxTraceStart);
		TraceEnd->SetRelativeLocation(Data.BoxTraceEnd);
		float AttackCost = CombatComponent->GetAttackCost(AttackAnimationData, InAttackCount);
		CombatComponent->AdjustStamina(-1 * AttackCost);
	}
	else
	{
		Execute_ResetCombatVariables(this);
	}
}
