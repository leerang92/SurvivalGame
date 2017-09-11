// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemInfo.h"
#include "Button.h"
#include "TextBlock.h"
#include "SlateBrush.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void SetItemInfo(FItemInformation Info);

	void SetAmount();

	FORCEINLINE bool GetSlotEmpty() const {
		return ItemInfo.Image == nullptr;
	}

protected:
	void SetSlotStyle(UTexture2D* ItemImage);
	
public:
	FItemInformation ItemInfo;

	UPROPERTY()
	UButton* SlotButton;

	UPROPERTY()
	UTextBlock* AmountText;
};
