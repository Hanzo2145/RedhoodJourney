// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/EnemyBase.h"

#include "AI/RedAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	RedAIController->GetBlackboardComponent()->SetValueAsObject(FName("CombatTarget"), InCombatTarget);
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
	RedAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), false);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}
