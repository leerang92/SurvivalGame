// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleCol->SetCapsuleRadius(50.0f);
	RootComponent = CapsuleCol;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	Mesh->SetStaticMesh(ProjectileMesh.Object);
	Mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	Mesh->AttachTo(CapsuleCol);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectle Component"));
	ProjectileComp->SetUpdatedComponent(CapsuleCol);
	ProjectileComp->InitialSpeed = 2000.0f;
	ProjectileComp->MaxSpeed = 2000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = true;
	ProjectileComp->Bounciness = 0.3f;
	ProjectileComp->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::FireDirection(const FVector& Dir)
{
	ProjectileComp->Velocity = Dir * ProjectileComp->InitialSpeed;
}
