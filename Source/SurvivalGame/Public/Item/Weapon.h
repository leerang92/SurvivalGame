// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponType.h"
#include "Projectile.h"
#include "WeaponClip.h"
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
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	void SetOwnerPawn(APawn* Pawn);

	/* 무기 장착 */
	virtual void OnEquip(EWeaponSlot Slot = EWeaponSlot::Hand);

	void OnUnEquip();

	virtual void AttachToWeapon(APawn* Pawn);

	/* 무기 발사 */
	void StartFire();

	void StopFire();

	void StartReload();

	void StopReload();

	FORCEINLINE bool GetWeaponState() const { return CurrentState == EWeaponState::Fire; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 발사체 생성 및 발사
	void OnShot();

	virtual void OnReload();

	FORCEINLINE FVector GetMuzzleLocation() const {
		return Mesh->GetSocketLocation(TEXT("MuzzleSocket"));
	}

	float SetAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	void PlayWeaponSound(USoundCue* SoundCue);

	bool IsFire() const;

	bool IsReload() const;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ReloadAnim;

	// 드랍 무기 아이템 클래스
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class APickupWeapon> PickupWeaponClass;

	// 발사체 클래스
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	// 발사 간격
	UPROPERTY(EditAnywhere, Category = "Variable")
	float FireInterval;

	UPROPERTY(EditAnywhere, Category = "Variable")
	int MaxAmmo;

	/* 사운드 */
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* ReloadSound;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* ClipMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeaponClip> ClipClass;

	class AWeaponClip* Clip;

protected:
	UPROPERTY(Transient)
	class APawn* MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type", meta = (AllowPrivateAccess = "true"))
	EWeaponSlot WeaponSlot;

	EWeaponState CurrentState;

	FTimerHandle ReloadTimerHandle;

	int CurrentAmmo;

	float NextInterval;

	bool bReloading;
};
