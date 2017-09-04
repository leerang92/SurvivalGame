// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "WeaponG36C.h"

void AWeaponG36C::OnEquip(EWeaponSlot Slot)
{
	Super::OnEquip(Slot);

	Mesh->SetRelativeLocation(SetWeaponLocation);
}

void AWeaponG36C::OnReload()
{
	Super::OnReload();

	if (Clip) 
	{
		Clip->OnUnEquip();
	}
}

