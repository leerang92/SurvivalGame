// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponType.h"
#include "Weapon.generated.h"

class APickupWeapon;

UENUM()
enum class EWeaponState
{
	Idle,
	Fire,
	Equip,
	Reload
};

UCLASS()
class SURVIVALGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class APickupWeapon> PickupWeaponClass;

	void SetOwnerPawn(APawn* Pawn);

	void OnEquip(EWeaponSlot Slot = EWeaponSlot::Hand);

	void OnUnEquip();

	void AttachToWeapon(APawn* Pawn);

protected:
	UPROPERTY(Transient)
	class APawn* MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type", meta = (AllowPrivateAccess = "true"))
	EWeaponSlot WeaponSlot;

public:
	
	void StartFire();
	
	void StopFire();

	void StartReload();
	
};
