// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RedAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API ARedAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARedAIController();
	
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
