// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;

	/* 콜리더 설정 */
	CapsuleCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleCol->SetCapsuleRadius(10.0f);
	CapsuleCol->SetCapsuleHalfHeight(10.0f);
	CapsuleCol->BodyInstance.SetCollisionProfileName(TEXT("Proejctile"));
	CapsuleCol->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	RootComponent = CapsuleCol;

	/* 메쉬 설정 */
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMesh(TEXT("StaticMesh'/Game/Meshes/Projectile/SM_Projectile.SM_Projectile'"));
	Mesh->SetStaticMesh(ProjectileMesh.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 컬리더 없음
	Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	Mesh->AttachTo(CapsuleCol);

	/* 무브먼트 컴포넌트 설정 */
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectle Component"));
	ProjectileComp->SetUpdatedComponent(CapsuleCol);
	ProjectileComp->InitialSpeed = 2000.0f;
	ProjectileComp->MaxSpeed = 2000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = true;
	ProjectileComp->Bounciness = 0.3f;
	ProjectileComp->ProjectileGravityScale = 0.0f;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		AActor* Actor = Cast<AActor>(OtherActor);
		if (Actor)
		{
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			Actor->TakeDamage(Damage, DamageEvent, nullptr, this);
		}
	}
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
