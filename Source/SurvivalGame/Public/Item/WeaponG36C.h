// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Weapon.h"
#include "WeaponG36C.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AWeaponG36C : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void OnEquip(EWeaponSlot Slot = EWeaponSlot::Hand) override;

	void OnUnEquip();

	virtual void OnReload() override;
public:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FVector SetWeaponLocation;

	FTimerHandle Timer;
};
