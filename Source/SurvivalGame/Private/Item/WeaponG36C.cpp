// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "WeaponG36C.h"

void AWeaponG36C::OnEquip(EWeaponSlot Slot)
{
	Super::OnEquip(Slot);

	Mesh->SetRelativeLocation(SetWeaponLocation);

	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &AWeaponG36C::OnUnEquip, 3.0f, false);
}

void AWeaponG36C::OnUnEquip()
{
	ClipMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	ClipMesh->SetSimulatePhysics(true);
	ClipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeaponG36C::OnReload()
{
	Super::OnReload();

	if (Clip) 
	{
		Clip->OnUnEquip();
	}
}

