// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogClass, Warning, TEXT("Construct"));
	SlotButton->OnClicked.AddDynamic(this, &UItemSlot::OnClick);
}


void UItemSlot::SetItemInfo(FItemInformation Info)
{
	ItemInfo = Info;

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

	// 기본 상태의 버튼 스타일 정의
	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);

	// Hovered, Pressed 상타의 버튼 스타일 정의
	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 0.4f);
	BtnStyle.SetHovered(SBrush);
	BtnStyle.SetPressed(SBrush);

	if(SlotButton)
		SlotButton->SetStyle(BtnStyle);
}

void UItemSlot::OnClick()
{
	UE_LOG(LogClass, Warning, TEXT("Click"));
	/*APlayerController* PC = Cast<APlayerController>(GetOwningPlayer());
	if (PC)
	{
	
		float PrevMouseX = 0.0f, PrevMouseY = 0.0f;
		float CurrentMouseX, CurrentMouseY;
		PC->GetMousePosition(CurrentMouseX, CurrentMouseY);

		if (PrevMouseX == CurrentMouseX || PrevMouseY == CurrentMouseY)
		{
			PrevMouseX = CurrentMouseX;
			PrevMouseY = CurrentMouseY;
			UE_LOG(LogClass, Warning, TEXT("Same Position"));
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("No Same Position"));
		}
	}*/
}
