// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UIInventory.h"


void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();

	CreateItemSlot();
}

void UUIInventory::CreateItemSlot()
{
	if (!SlotClass)
	{
		return;
	}

	for (int32 i = 0; i < SlotSize; ++i)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), SlotClass);
		if (Widget)
		{
			AddGridSlot(SlotPanel->AddChildToUniformGrid(Widget));

			UItemSlot* Slot = Cast<UItemSlot>(Widget);
			SlotList.Add(Slot);
		}
	}
}

void UUIInventory::AddGridSlot(UUniformGridSlot * Grid)
{
	Grid->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	Grid->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	Grid->SetColumn(Column);
	Grid->SetRow(Row);
	
	IncrementSlotMatrix();
}

void UUIInventory::AddSlotItem(FItemInformation Info)
{
	bool IsAdd = false;
	for (int32 i = 0; i < SlotList.Num(); ++i)
	{
		if (SlotList[i]->ItemInfo.Name == Info.Name)
		{
			SlotList[i]->ItemInfo.Amount += Info.Amount;
			SlotList[i]->SetAmount();
			IsAdd = true;
			break;
		}
	}
	if (!IsAdd)
	{
		for (int32 i = 0; i < SlotList.Num(); ++i)
		{
			if (SlotList[i]->GetSlotEmpty())
			{
				SlotList[i]->SetItemInfo(Info);
				break;
			}
		}
	}
}

void UUIInventory::IncrementSlotMatrix()
{

	Column++;
	if (Column >= ColumnLength)
	{
		Column = 0;
		Row++;
	}
}
