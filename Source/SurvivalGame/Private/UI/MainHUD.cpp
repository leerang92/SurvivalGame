// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UsableActor.h"
#include "PlayerCharacter.h"
#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (Inventory)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Equipment)
	{
		Equipment->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Pickup)
	{
		Pickup->SetVisibility(ESlateVisibility::Hidden);
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

void UMainHUD::SetEquipment(bool bShow)
{
	if (bShow)
	{
		Equipment->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Equipment->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::ShowPickupUI(bool bShow)
{
	if (bShow)
	{
		Pickup->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Pickup->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::DropItem(UClass * ItemClass, int Index)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (ItemClass != nullptr && PC)
	{
		const FVector SpawnVec = (PC->GetActorForwardVector() * 100.0f) + PC->GetActorLocation();
		const FRotator SpawnRot = PC->GetActorRotation();

		AUsableActor* Item = GetWorld()->SpawnActor<AUsableActor>(ItemClass, SpawnVec, SpawnRot);

		Inventory->ConstructSlot(Index);
	}
}
