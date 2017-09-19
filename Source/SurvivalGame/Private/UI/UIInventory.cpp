// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UIInventory.h"

void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();

	PrevMouseX = 0.0f;
	PrevMouseY = 0.0f;

	CreateInventory();
}

void UUIInventory::CreateInventory()
{
	if (!SlotClass)
	{
		UE_LOG(LogClass, Warning, TEXT("Slot Class 없음"));
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
			Slot->SetSlotIndex(i);
		}
	}
}

void UUIInventory::AddSlotItem(FItemInformation Info)
{
	if (Info.Image == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("잘못된 아이템 정보"));
		return;
	}

	bool IsAdd = false;
	// 중복 여부 검사 후 중복 시 갯수만 증가
	for (int32 i = 0; i < SlotList.Num(); ++i)
	{
		if (SlotList[i]->GetItemInfo().Name == Info.Name)
		{
			FItemInformation NewInfo = SlotList[i]->GetItemInfo();
			NewInfo.Amount += Info.Amount;
			SlotList[i]->SetItemInfo(NewInfo);
			IsAdd = true;
			break;
		}
	}
	// 중복된 아이템 없을 시 빈슬롯에 아이템 추가
	if (!IsAdd)
	{
		for (int32 i = 0; i < SlotList.Num(); ++i)
		{
			if (SlotList[i]->IsEmpty())
			{
				SlotList[i]->SetItemInfo(Info);
				break;
			}
		}
	}
}

void UUIInventory::ChangeSlot(int ToIndex, int FromIndex)
{
	FItemInformation ToItem;
	ToItem = SlotList[ToIndex]->GetItemInfo();
	SlotList[FromIndex]->SetItemInfo(ToItem);

	// 이전 슬롯 초기화
	ToItem = {};
	SlotList[ToIndex]->SetItemInfo(ToItem);
}

void UUIInventory::AddGridSlot(UUniformGridSlot * Grid)
{
	Grid->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	Grid->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	Grid->SetColumn(Column);
	Grid->SetRow(Row);
	
	IncrementSlotMatrix();
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