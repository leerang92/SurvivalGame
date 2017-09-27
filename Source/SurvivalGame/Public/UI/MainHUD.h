// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIInventory.h"
#include "UIEquipment.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void SetInventory(bool bShow);

	void SetEquipment(bool bShow);

	void ShowPickupUI(bool bShow);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void DropItem(UClass* ItemClass, int Index);

public:
	UPROPERTY(BlueprintReadWrite, Category = "UMG")
	class UUIEquipment* Equipment;

	UPROPERTY(BlueprintReadWrite, Category = "UMG")
	class UUIInventory* Inventory;

	UPROPERTY(BlueprintReadWrite, Category = "UMG")
	class UUserWidget* Pickup;
};
