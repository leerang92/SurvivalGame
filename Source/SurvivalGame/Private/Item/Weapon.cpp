// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	WeaponMesh->AttachTo(Capsule);

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
		MyPawn = Cast<APlayerCharacter>(Pawn);
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

