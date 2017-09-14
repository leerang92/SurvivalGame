// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UIInventory.h"

void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();
	bCanEverTick = true;

	CreateInventory();
}

void UUIInventory::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UE_LOG(LogClass, Warning, TEXT("!!!!"));
}

void UUIInventory::CreateInventory()
{
	if (!SlotClass)
	{
		UE_LOG(LogClass, Warning, TEXT("Slot Class ����"));
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

void UUIInventory::AddSlotItem(FItemInformation Info)
{
	if (Info.Image == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("�߸��� ������ ����"));
		return;
	}

	bool IsAdd = false;
	// �ߺ� ���� �˻� �� �ߺ� �� ������ ����
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
	// �ߺ��� ������ ���� �� �󽽷Կ� ������ �߰�
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
