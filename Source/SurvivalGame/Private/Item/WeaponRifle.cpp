// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "WeaponRifle.h"

void AWeaponRifle::BeginPlay()
{
	Super::BeginPlay();

	Clip = GetWorld()->SpawnActor<AWeaponClip>(ClipClass, Mesh->GetSocketLocation(TEXT("ClipSocket")), FRotator::ZeroRotator);
	if (Clip)
	{
		Clip->OnEquip(Mesh);
	}
}

void AWeaponRifle::OnReload()
{
	Super::OnReload();

	if (Clip)
	{
		Clip->OnUnEquip();
	}
}
