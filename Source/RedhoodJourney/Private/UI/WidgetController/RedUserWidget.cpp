// Copyright belong to Anas (Hanzo) Hatachi


#include "UI/WidgetController/RedUserWidget.h"


void URedUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
