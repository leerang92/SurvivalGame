// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/UsableActor.h"
#include "Weapon.h"
#include "PickupWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API APickupWeapon : public AUsableActor
{
	GENERATED_BODY()
	
public:
	APickupWeapon();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AWeapon> WeaponClass;

	virtual void OnUsed(APawn* Owner) override;
};
