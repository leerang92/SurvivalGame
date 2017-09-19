// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Blueprint/UserWidget.h"
#include "UISlot.h"
//#include "ItemInfo.h"
//#include "Button.h"
//#include "TextBlock.h"
//#include "SlateBrush.h"
//#include "Image.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UItemSlot : public UUISlot
{
	GENERATED_BODY()
		
public:
	//UFUNCTION(BlueprintCallable, Category = "Slot")
	virtual void ChangeSlot(int ToIndex) override;
};
