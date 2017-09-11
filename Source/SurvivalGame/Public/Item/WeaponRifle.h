// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Weapon.h"
#include "Item/WeaponClip.h"
#include "WeaponRifle.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AWeaponRifle : public AWeapon
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	void CreateClip(FName AttachPoint = "ClipSocket");

	FORCEINLINE AWeaponClip* GetClip() const { return Clip; }

protected:

	virtual void OnReload() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponClip", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponClip> ClipClass;

	UPROPERTY()
	AWeaponClip* Clip;
	
	
};
