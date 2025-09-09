// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/Redhood.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Camera/CameraComponent.h"
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

void ARedhood::Attack_Implementation()
{
	GetPaperZDComponent()->GetAnimInstance()->PlayAnimationOverride(AttackAnimation);
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
