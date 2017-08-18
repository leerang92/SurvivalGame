// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Weapon.generated.h"

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
	class USkeletalMeshComponent* WeaponMesh;

	void SetOwnerPawn(APawn* Pawn);

	FORCEINLINE class APlayerCharacter* GetOwnerPawn() const { return MyPawn; }
	
protected:
	UPROPERTY(Transient)
	class APlayerCharacter* MyPawn;

public:
	
	void StartFire();
	
	void StopFire();

	void StartReload();
	
};
