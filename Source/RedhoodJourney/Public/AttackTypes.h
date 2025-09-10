

#pragma once
#include "CoreMinimal.h"
#include "PaperZD/Public/AnimSequences/PaperZDAnimSequence.h"
#include "AttackTypes.generated.h"

USTRUCT(BlueprintType)
struct FAttack
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPaperZDAnimSequence> AttackAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDamage = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceStart = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceEnd = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceExtent = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StaminaCost = 0.f;
};