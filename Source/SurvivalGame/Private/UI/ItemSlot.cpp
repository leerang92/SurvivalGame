// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "ItemSlot.h"
//
//void UItemSlot::SetItemInfo(FItemInformation Info)
//{
//	ItemInfo = Info;
//
//	SetSlotStyle(ItemInfo.Image);
//}
//
//void UItemSlot::SetSlotStyle(UTexture2D* Image)
//{
//	FSlateBrush Brush;
//	if (Image) // �̹��� ���� �� ������ �̹�����
//	{
//		Brush.SetResourceObject(Image);
//		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	}
//	else // �̹��� ���� �� �����ϰ�
//	{
//		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
//	}
//	ItemImage->SetBrush(Brush);
//
//	SetAmount();
//}
//
//void UItemSlot::SetAmount()
//{
//	/* ������ ���� */
//	if (ItemInfo.Amount > 0)
//		AmountText->SetText(FText::AsNumber(ItemInfo.Amount));
//	else
//		AmountText->SetText(FText::GetEmpty());
//}
//
//void UItemSlot::ChangeSlot(int ToIndex)
//{
//	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwningPlayerPawn());
//	if (PC)
//	{
//		PC->InventoryComp->MainHUD->Inventory->ChangeSlot(ToIndex, SlotIndex);
//	}
//}

void UItemSlot::ChangeSlot(int ToIndex)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PC->InventoryComp->MainHUD->Inventory->ChangeSlot(ToIndex, SlotIndex);
	}
}

