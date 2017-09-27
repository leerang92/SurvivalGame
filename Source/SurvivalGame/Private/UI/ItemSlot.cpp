// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "ItemSlot.h"

void UItemSlot::ChangeSlot(int ToIndex)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PC->MainHUD->Inventory->ChangeSlot(ToIndex, SlotIndex);
	}
}

