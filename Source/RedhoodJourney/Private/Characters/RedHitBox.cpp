// Copyright belong to Anas (Hanzo) Hatachi


#include "Characters/RedHitBox.h"

#include "PaperZDAnimInstance.h"
#include "Interfaces/CombatInterface.h"

void URedHitBox::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance->GetOwningActor()->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_AttackTrace(OwningInstance->GetOwningActor());
	}
}
