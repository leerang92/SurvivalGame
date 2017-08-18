// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "Inventory.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponSlotNum = 3;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddWeapon(AWeapon * NewWeapon)
{
	if (WeaponList.Num() <= WeaponSlotNum) 
	{
		WeaponList.Add(NewWeapon);

		UE_LOG(LogClass, Warning, TEXT("%d"), WeaponList.Num());
	}
}

