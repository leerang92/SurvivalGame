// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponType.h"
#include "Projectile.h"
#include "Weapon.generated.h"

class APickupWeapon;

UENUM()
enum class EWeaponState
{
	Idle,
	Fire,
	Equip,
	Reload,
	Swap,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle		UMETA(DisplayName = "Rifle"),
	Shotgun		UMETA(DisplayName = "Shotgun"),
};

UCLASS()
class SURVIVALGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	void SetOwnerPawn(APawn* Pawn);

	/* ���� ���� */
	virtual void OnEquip(EWeaponSlot Slot = EWeaponSlot::Hand);

	void OnUnEquip();

	virtual void AttachToWeapon(APawn* Pawn);

	/* ���� �߻� */
	void StartFire();

	void StopFire();

	void SetState(EWeaponState State);

	virtual void OnReload();

	virtual void FinishReload();

	float SetAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	FORCEINLINE bool GetWeaponState() const { return CurrentState == EWeaponState::Fire; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �߻�ü ���� �� �߻�
	void OnFire();

	FORCEINLINE FVector GetMuzzleLocation() const {
		return Mesh->GetSocketLocation(TEXT("MuzzleSocket"));
	}

	void PlayWeaponSound(USoundCue* SoundCue);

	UParticleSystemComponent* PlayEffect(UParticleSystem* Effect, FName AttachPoint = "MuzzleSocket");

	void StopEffect();

	UAudioComponent* PlaySound(USoundCue* Sound, FName AttachPoint = "MuzzleSocket");

	void StopSound();

	void SetWeaponState();

	bool IsFire() const;

	bool IsReload() const;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FVector SetWeaponLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ReloadAnim;

	UPROPERTY(EditAnywhere, Category = "Image")
	UTexture2D* WeaponImage;

	// ��� ���� ������ Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class APickupWeapon> PickupWeaponClass;

	// �߻�ü Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	// �߻� ����
	UPROPERTY(EditAnywhere, Category = "Variable")
	float FireInterval;

	UPROPERTY(EditAnywhere, Category = "Variable")
	int MaxAmmo;

	/* ���� */
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* ReloadSound;

	UPROPERTY()
	UAudioComponent* AudioComp;

	/* ����Ʈ */
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* MuzzleFX;

	UPROPERTY()
	UParticleSystemComponent* WeaponFXComp;

	UPROPERTY(EditAnywhere, Category = "Weapon Type")
	EWeaponType WeaponType;

protected:
	UPROPERTY(Transient)
	class APawn* MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type", meta = (AllowPrivateAccess = "true"))
	EWeaponSlot WeaponSlot;

	EWeaponState CurrentState;

	FTimerHandle ReloadTimerHandle;

	FTimerHandle FireTimerHandle;

	int CurrentAmmo;

	bool bReloading;

	bool bFire;
};
