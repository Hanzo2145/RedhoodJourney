// Copyright belong to Anas (Hanzo) Hatachi


#include "AI/RedAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ARedAIController::ARedAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard Componenet");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
	check(BehaviorTreeComponent);
}
