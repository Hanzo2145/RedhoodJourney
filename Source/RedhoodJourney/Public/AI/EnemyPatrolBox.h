// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPatrolBox.generated.h"

class ABaseCharacter;
class AEnemyBase;
UCLASS()
class REDHOODJOURNEY_API AEnemyPatrolBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPatrolBox();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AEnemyBase*> PatrolEnemies;
	
};
