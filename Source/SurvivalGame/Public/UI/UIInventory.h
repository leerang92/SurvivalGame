// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemSlot.h"
#include "ItemInfo.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "UIInventory.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UUIInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	void AddSlotItem(FItemInformation Info);

	void ChangeSlot(int ToIndex, int FromIndex);

protected:

	void CreateInventory();

	// UniformGrid에 아이템 슬롯 지정하여 정렬
	void AddGridSlot(UUniformGridSlot* Grid);

	// 슬롯 행렬 증가
	void IncrementSlotMatrix();

public:
	UPROPERTY(EditAnywhere, Category = "Inventroy")
	TSubclassOf<class UUserWidget> SlotClass;

private:
	UPROPERTY()
	TArray<class UItemSlot*> SlotList;

	UPROPERTY()
	class UUniformGridPanel* SlotPanel;

	UPROPERTY(EditAnywhere, Category = "Variable", meta = (PrivateAllowAccess = true))
	int SlotSize;

	UPROPERTY(EditAnywhere, Category = "Variable", meta = (PrivateAllowAccess = true))
	int ColumnLength;

	int Column;
	int Row;

	bool bDrag : 1;

	bool bPosition : 1;
	
	float PrevMouseX, PrevMouseY;
};
