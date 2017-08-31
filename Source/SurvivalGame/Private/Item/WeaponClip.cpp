// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "WeaponClip.h"


// Sets default values
AWeaponClip::AWeaponClip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LifeTime = 60.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = MeshComp;
}


void AWeaponClip::OnEquip(USceneComponent* InParent, FName AttachPoint)
{
	MeshComp->AttachToComponent(InParent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	MeshComp->SetSimulatePhysics(false);
}

void AWeaponClip::OnUnEquip()
{
	MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	MeshComp->SetSimulatePhysics(true);

	GetWorld()->GetTimerManager().SetTimer(DestoryTimerHandle, this, &AWeaponClip::OnDestroy, LifeTime, false);
}

void AWeaponClip::OnDestroy()
{
	Destroy();
}

