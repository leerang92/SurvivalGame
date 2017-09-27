// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "PickupWeapon.h"

APickupWeapon::APickupWeapon()
{
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetRelativeRotation(FRotator(90.0f, 0, 0));
}

void APickupWeapon::BeginPlay()
{
	
}

void APickupWeapon::OnUsed(APawn * Owner)
{
	APlayerCharacter* MyPawn = Cast<APlayerCharacter>(Owner);

	if (MyPawn)
	{
		Super::OnUsed(Owner);

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);

		MyPawn->InventoryComp->AddWeapon(NewWeapon);
	}
}
