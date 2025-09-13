// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageNumber.generated.h"

/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API UDamageNumber : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNumber(float InDamage, const FSlateColor& InColor);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DamageText;
	
};
