// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "PickupWeapon.h"
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

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::SetOwnerPawn(APawn * OwnerPawn)
{
	MyPawn = OwnerPawn;
}

void UInventory::SwapWeapon(const int Index)
{
	if (WeaponList.Num() > Index)
	{
		SetCurrentWeapon(WeaponList[Index], CurrentWeapon);
	}
}

void UInventory::AddWeapon(AWeapon * NewWeapon)
{
	if (WeaponList.Num() <= WeaponSlotNum) 
	{
		WeaponList.Add(NewWeapon);
		NewWeapon->AttachToWeapon(MyPawn);

		//ó�� ���� ���� ��
		if (WeaponList.Num() > 0 && CurrentWeapon == nullptr)
		{
			SetCurrentWeapon(WeaponList[0], CurrentWeapon);
		}
	}
}

void UInventory::SetCurrentWeapon(AWeapon * NewWeapon, AWeapon* LastWeapon)
{
	if (CurrentWeapon == NewWeapon)
		return;

	// ���� Ŭ������ �ӽ÷� ������ ����
	AWeapon* PrevWeapon = nullptr;

	if (LastWeapon)
	{
		PrevWeapon = LastWeapon;
	}
	else if (CurrentWeapon != NewWeapon)
	{
		PrevWeapon = NewWeapon;
	}
	// ��ü�ϴ� ���⸦ �ٸ� ���� ����
	if (PrevWeapon)
	{
		PrevWeapon->AttachToWeapon(MyPawn);
	}

	// ���� ������ ���� Ŭ������ ��� �տ� ����
	CurrentWeapon = NewWeapon;

	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwnerPawn(MyPawn);
		CurrentWeapon->OnEquip();
	}
}

void UInventory::DropItem()
{
	const FVector DropLoc = MyPawn->GetActorForwardVector() + MyPawn->GetActorLocation();
	const FRotator DropRot = MyPawn->GetActorRotation();

	if (CurrentWeapon)
	{
		APickupWeapon* DropWeapon = GetWorld()->SpawnActor<APickupWeapon>(CurrentWeapon->PickupWeaponClass, DropLoc, DropRot);

		if (DropWeapon)
		{
			RemoveWeapon();
		}
	}
}

void UInventory::RemoveWeapon()
{
	for (int32 i = 0; i < WeaponList.Num(); ++i)
	{
		if (WeaponList[i] == CurrentWeapon)
		{
			WeaponList.RemoveAt(i);
			break;
		}
	}
	CurrentWeapon->Destroy();
	CurrentWeapon = nullptr;
}

FName UInventory::GetWeaponType(const EWeaponSlot GetSlot) const
{
	switch (GetSlot)
	{
	case EWeaponSlot::Hand: // ��
		return AttachHand;
	case EWeaponSlot::Primary: // �ֹ���
		return AttachPrimary;
	case EWeaponSlot::Secondary: // ��������
		return AttachSecondery;
	default:
		return "";
	}
}

