// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/EnemyBase.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "AI/RedAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	RedAIController->GetBlackboardComponent()->SetValueAsObject(FName("CombatTarget"), InCombatTarget);
}

void AEnemyBase::Attack_Implementation()
{
	GetPaperZDComponent()->GetAnimInstance()->PlayAnimationOverride(AttackAnimation);
}

AEnemyBase::AEnemyBase()
{
	
}

void AEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	RedAIController = Cast<ARedAIController>(NewController);

	RedAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	RedAIController->RunBehaviorTree(BehaviorTree);
	RedAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsAlive"), true);
}

void AEnemyBase::HandleDeath(bool IsDead)
{
	Super::HandleDeath(IsDead);
	EnemyIsDead = true;
	if (RedAIController)
	{
		if (UBlackboardComponent* BB = RedAIController->GetBlackboardComponent())
		{
			BB->SetValueAsBool(TEXT("IsAlive"), false);
		}
		RedAIController->ClearFocus(EAIFocusPriority::Gameplay);
		RedAIController->StopMovement();
	}
	GetCharacterMovement()->DisableMovement();
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}
