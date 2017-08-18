// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "PickupWeapon.h"

void APickupWeapon::OnUsed(APawn * Owner)
{
	APlayerCharacter* MyPawn = Cast<APlayerCharacter>(Owner);

	if (MyPawn)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		const FVector SpawnLocation = MyPawn->GetActorLocation() + (MyPawn->GetActorForwardVector() * 10.0f);
		AWeapon* NewWeapon = MyPawn->GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnLocation, FRotator::ZeroRotator, SpawnParam);

		MyPawn->Inventory->AddWeapon(NewWeapon);
		//MyPawn->Inventory->AddWeapon(WeaponClass->GetDefaultObject<AWeapon>());

		Super::OnUsed(Owner);
	}
}
