// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "ItemSlot.h"


void UItemSlot::SetItemInfo(FItemInformation Info)
{
	ItemInfo = Info;
	//UE_LOG(LogClass, Warning, TEXT("Set Item"));
	SetSlotStyle(ItemInfo.Image);
	SetAmount();
}

void UItemSlot::SetAmount()
{
	if (ItemInfo.Amount)
	{
		if (ItemInfo.Amount > 0)
			AmountText->SetText(FText::AsNumber(ItemInfo.Amount));
		else
			AmountText->SetText(FText::GetEmpty());
	}
}

void UItemSlot::SetSlotStyle(UTexture2D * ItemImage)
{
	if (ItemImage == nullptr)
		return;

	FSlateBrush SBrush;

	SBrush.ImageSize = FVector2D(32.0f, 32.0f);
	SBrush.SetResourceObject(ItemImage);

	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);

	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 0.4f);
	BtnStyle.SetHovered(SBrush);
	BtnStyle.SetPressed(SBrush);

	if(SlotButton)
		SlotButton->SetStyle(BtnStyle);
}
