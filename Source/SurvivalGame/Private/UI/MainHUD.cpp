// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (Inventory)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::SetInventory(bool bShow)
{
	if (bShow)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!bShow)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
}