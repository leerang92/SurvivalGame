// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PickupActor.h"


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAllowRespawn = true;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::OnUsed(APawn * OwnerPawn)
{
	Super::OnUsed(OwnerPawn);

	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());

	SetPickupActor();

	if (bAllowRespawn)
	{
		FTimerHandle RespawnTimer;
	}
	else
	{
		Destroy();
	}
}

void APickupActor::SetPickupActor()
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(false);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APickupActor::OnRespawn()
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(true);
	}
}

