// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerAnim.h"

void UPlayerAnim::AnimNotify_CreateClip(UAnimNotify* Notify)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PC)
	{
		AWeaponRifle* Weapon = Cast<AWeaponRifle>(PC->InventoryComp->GetCurrentWeapon());
		if (Weapon)
		{
			Weapon->CreateClip(TEXT("hand_L"));
			if (Weapon->GetClip())
			{
				Weapon->GetClip()->OnEquip(PC->GetMesh(), TEXT("hand_L"));
			}
		}
	}
}

void UPlayerAnim::AnimNotify_AttachClip(UAnimNotify * Notify)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PC)
	{
		AWeaponRifle* Weapon = Cast<AWeaponRifle>(PC->InventoryComp->GetCurrentWeapon());
		if (Weapon && Weapon->GetClip())
		{
			Weapon->GetClip()->OnEquip(Weapon->GetMesh());
		}
	}
}
