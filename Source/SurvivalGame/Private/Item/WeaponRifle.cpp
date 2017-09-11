// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "WeaponRifle.h"

void AWeaponRifle::BeginPlay()
{
	Super::BeginPlay();

	CreateClip();
	if (Clip)
	{
		Clip->OnEquip(Mesh);
	}
}

void AWeaponRifle::CreateClip(FName AttachPoint)
{
	Clip = GetWorld()->SpawnActor<AWeaponClip>(ClipClass, Mesh->GetSocketLocation(AttachPoint), FRotator::ZeroRotator);
}

void AWeaponRifle::OnReload()
{
	Super::OnReload();

	if (Clip)
	{
		Clip->OnUnEquip();
		Clip = nullptr;
	}
}
