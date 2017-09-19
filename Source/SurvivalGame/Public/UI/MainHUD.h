// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIInventory.h"
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

	void SetInventory(bool bShow);

	void SetEquipment(bool bShow);

public:
	UPROPERTY(EditAnywhere, Category = "UMG")
	TSubclassOf<class UUserWidget> EquipmentClass;

	UPROPERTY(BlueprintReadWrite, Category = "UMG")
	class UUIInventory* Inventory;
};
