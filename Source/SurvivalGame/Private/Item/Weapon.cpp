// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSlot = EWeaponSlot::Primary;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->AttachTo(Capsule);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SetOwnerPawn(APawn * Pawn)
{
	if(Pawn && MyPawn != Pawn)
	{
		MyPawn = Pawn;
	}
}

void AWeapon::OnEquip(EWeaponSlot Slot)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(MyPawn);
	if (PC)
	{
		FName AttachPoint = PC->Inventory->GetWeaponType(Slot);
		Mesh->AttachToComponent(PC->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	}
}

void AWeapon::OnUnEquip()
{
}

void AWeapon::AttachToWeapon(APawn* Pawn)
{
	SetOwnerPawn(Pawn);
	OnEquip(WeaponSlot);
}

void AWeapon::StartFire()
{
}

void AWeapon::StopFire()
{
}

void AWeapon::StartReload()
{
}

