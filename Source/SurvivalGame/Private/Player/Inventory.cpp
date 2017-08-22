// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "Inventory.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponSlotNum = 3;

	AttachHand = TEXT("Hand_r");
	AttachPrimary = TEXT("Primary");
	AttachSecondery = TEXT("Secondery");

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventory::SetOwnerPawn(APawn * OwnerPawn)
{
	MyPawn = OwnerPawn;
}

void UInventory::EquipWeapon(AWeapon * NewWeapon)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MyPawn);
	if (Character)
	{
		NewWeapon->Mesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
	}
}

void UInventory::RemoveWeapon()
{
	CurrentWeapon->Destroy();
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
		NewWeapon->AttachToWeapon(MyPawn);
		
		if (WeaponList.Num() > 0 && CurrentWeapon == nullptr)
		{
			SetCurrentWeapon(WeaponList[0]);
		}
	}
}

void UInventory::SetCurrentWeapon(AWeapon * NewWeapon)
{
	if (NewWeapon)
	{
		CurrentWeapon = NewWeapon;
		CurrentWeapon->SetOwnerPawn(MyPawn);
		CurrentWeapon->OnEquip();
	}
}

FName UInventory::GetWeaponType(EWeaponSlot GetSlot) const
{
	switch (GetSlot)
	{
	case EWeaponSlot::Hand:
		return AttachHand;
	case EWeaponSlot::Primary:
		return AttachPrimary;
	case EWeaponSlot::Secondary:
		return AttachSecondery;
	default:
		return "";
	}
}

