// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UISlot.h"
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
