// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfo.h"
#include "TextBlock.h"
#include "Image.h"
#include "SlateBrush.h"
#include "UISlot.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UUISlot : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void SetItemInfo(FItemInformation Info);
	
	virtual void SetAmountText();

	UFUNCTION(BlueprintCallable, Category = "Slot")
	virtual void ChangeSlot(int ToIndex);

	void SetSlotIndex(int Index);

	FORCEINLINE FItemInformation GetItemInfo() const { return ItemInfo; }

	UFUNCTION(BlueprintCallable, Category = "Slot")
	FORCEINLINE UTexture2D* GetItemImage() const { return ItemInfo.Image; }

	UFUNCTION(BlueprintCallable, Category = "Slot")
	FORCEINLINE int GetSlotIndex() const { return SlotIndex; }

	UFUNCTION(BlueprintCallable, Category = "Slot")
	FORCEINLINE bool IsEmpty() const { return ItemInfo.Image == nullptr; }

protected:

	virtual void SetSlotStyle(UTexture2D* Image);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Slot")
	class UTextBlock* AmountText;

	UPROPERTY(BlueprintReadWrite, Category = "Slot")
	class UImage* ItemImage;

protected:
	FItemInformation ItemInfo;

	int SlotIndex;
};
