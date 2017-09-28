// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "EquipActor.h"


// Sets default values
AEquipActor::AEquipActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandSocket = TEXT("hand_r");
	PrimarySocket = TEXT("Primary");
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AEquipActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipActor::SetEqiupWeapon(AWeapon * NewWeapon, FName AttachSlot)
{
	if (!NewWeapon)
		return;

	AWeapon* SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(NewWeapon->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	if (SpawnWeapon)
	{
		if (FirstWeapon == nullptr)
		{
			FirstWeapon = SpawnWeapon;
			FirstWeapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
		}
		else if (SecondWeapon == nullptr)
		{
			SecondWeapon = SpawnWeapon;
			SecondWeapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, PrimarySocket);
		}
	}
}

