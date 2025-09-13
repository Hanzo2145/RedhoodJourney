// Copyright belong to Anas (Hanzo) Hatachi


#include "UI/FloatingText/DamageNumber.h"
#include "Styling/SlateColor.h"
#include "Components/TextBlock.h"

void UDamageNumber::SetNumber(float InDamage, const FSlateColor& InColor)
{
	//UKismetTextLibrary::FloatToText(InDamage, RoundingMode.GetValue(), false, true, 1, 5, 0, 0);
	TEnumAsByte<ERoundingMode> RoundingMode;
	ERoundingMode Mode = static_cast<ERoundingMode>(RoundingMode);

	FNumberFormattingOptions NumFmt;
	NumFmt.AlwaysSign               = false;
	NumFmt.UseGrouping              = true;
	NumFmt.MinimumIntegralDigits    = 1;
	NumFmt.MaximumIntegralDigits    = 5;
	NumFmt.MinimumFractionalDigits  = 0;
	NumFmt.MaximumFractionalDigits  = 0;
	NumFmt.RoundingMode             = Mode;
	
	const FText Text = FText::AsNumber(InDamage, &NumFmt);
	if (ensure(DamageText))
	{
		DamageText->SetText(Text);
		DamageText->SetColorAndOpacity(InColor);
	}
}
