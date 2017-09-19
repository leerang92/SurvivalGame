// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UISlot.h"

void UUISlot::SetItemInfo(FItemInformation Info)
{
	ItemInfo = Info;
	SetSlotStyle(ItemInfo.Image);
}

void UUISlot::SetSlotStyle(UTexture2D * Image)
{
	FSlateBrush Brush;
	if (Image)
	{
		Brush.SetResourceObject(Image);
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
	}
	ItemImage->SetBrush(Brush);
	SetAmountText();
}

void UUISlot::SetAmountText()
{
	if(ItemInfo.Amount > 0)
		AmountText->SetText(FText::AsNumber(ItemInfo.Amount));
	else
		AmountText->SetText(FText::GetEmpty());
}

void UUISlot::ChangeSlot(int ToIndex)
{

}

void UUISlot::SetSlotIndex(int Index)
{
	SlotIndex = Index;
}
