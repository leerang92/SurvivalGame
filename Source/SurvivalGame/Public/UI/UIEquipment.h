// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UISlot.h"
#include "UIEquipment.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UUIEquipment : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetWeaponSlot(UTexture2D* Image);
	
	UPROPERTY(BlueprintReadWrite, Category = "Slot")
	class UUISlot* WeaponSlot1;

	UPROPERTY(BlueprintReadWrite, Category = "Slot")
	class UUISlot* WeaponSlot2;
};
