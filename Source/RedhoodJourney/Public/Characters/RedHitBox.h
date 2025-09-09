// Copyright belong to Anas (Hanzo) Hatachi

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "RedHitBox.generated.h"

/**
 * 
 */
UCLASS()
class REDHOODJOURNEY_API URedHitBox : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;
};
