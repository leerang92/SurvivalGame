// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "SlateBrush.h"
#include "UIEquipment.h"


void UUIEquipment::SetWeaponSlot(UTexture2D * Image)
{
	FSlateBrush Brush;
	if (Image)
	{
		Brush.SetResourceObject(Image);
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
	}

	if (WeaponSlot1->ItemImage->Brush.GetResourceObject() == nullptr)
	{
		WeaponSlot1->ItemImage->SetBrush(Brush);
	}
	else if (WeaponSlot2->ItemImage->Brush.GetResourceObject() == nullptr)
	{
		WeaponSlot2->ItemImage->SetBrush(Brush);
	}
		

}