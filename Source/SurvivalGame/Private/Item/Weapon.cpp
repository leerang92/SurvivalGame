// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSlot = EWeaponSlot::Primary;
	CurrentState = EWeaponState::Idle;

	bReloading = false;

	FireInterval = 0.15f;
	NextInterval = FireInterval;

	MaxAmmo = 30.0f;
	CurrentAmmo = MaxAmmo;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->AttachTo(Capsule);

	//ClipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Clip Mesh Component"));
	//ClipMesh->AttachTo(Mesh, TEXT("ClipSocket"));
	//ClipMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//ClipMesh->AttachTo(Capsule);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Clip = GetWorld()->SpawnActor<AWeaponClip>(ClipClass, Mesh->GetSocketLocation(TEXT("ClipSocket")), FRotator::ZeroRotator);
	if (Clip)
	{
		Clip->OnEquip(Mesh);
	}

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case EWeaponState::Idle:
		break;

	case EWeaponState::Fire:
		if (IsFire()) {
			NextInterval -= DeltaTime;

			if (NextInterval <= 0.0f && CurrentAmmo > 0)
			{
				OnShot();
				CurrentAmmo--;
				NextInterval = FireInterval;
			}
			else if (CurrentAmmo <= 0)
			{
				StartReload();
			}
		}
		break;

	case EWeaponState::Reload:
		if(IsReload())
			OnReload();
		break;
	}
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

void AWeapon::OnShot()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(MyPawn);
	if (PC)
	{
		/* 발사 방향 구하기 */
		const FVector CamLoc = PC->FollowCamera->GetComponentLocation();
		FRotator CamRot = PC->FollowCamera->GetComponentRotation();
		const FVector MuzzleLocation = GetMuzzleLocation();

		const FVector ZeroDir = CamRot.RotateVector(FVector::ForwardVector);
		const FVector ZeroPoint = (ZeroDir * 5000.0f) + CamLoc;
		FVector ProjectileDir = ZeroPoint - MuzzleLocation;
		ProjectileDir.Normalize();

		/* 발사체 스폰 */
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = PC;
		SpawnParam.Instigator = Instigator;

		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, CamRot, SpawnParam);
		if (NewProjectile) 
		{
			NewProjectile->FireDirection(ProjectileDir);
		}
	}
}

void AWeapon::OnReload()
{
	bReloading = true;
	CurrentAmmo = MaxAmmo;

	// 재장전 애니메이션 재생 후 재장전 완료
	float Duration = SetAnimation(ReloadAnim);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AWeapon::StopReload, Duration, false);

	PlayWeaponSound(ReloadSound);
}

float AWeapon::SetAnimation(UAnimMontage * Animation, float InPlayRate, FName StartSelectName)
{
	float Duration = 0.0f;
	APlayerCharacter* PC = Cast<APlayerCharacter>(MyPawn);
	if (PC)
	{
		Duration = PC->PlayAnimMontage(Animation, InPlayRate, StartSelectName);
	}
	return Duration;
}

void AWeapon::PlayWeaponSound(USoundCue * SoundCue)
{
	UAudioComponent* AC = nullptr;
	if (SoundCue && MyPawn)
	{
		AC = UGameplayStatics::SpawnSoundAttached(SoundCue, MyPawn->GetRootComponent());
	}
}

void AWeapon::StartFire()
{
	if (IsFire())
	{
		CurrentState = EWeaponState::Fire;
	}
}

void AWeapon::StopFire()
{
	if (CurrentState == EWeaponState::Fire)
	{
		CurrentState = EWeaponState::Idle;
	}
}

void AWeapon::StartReload()
{
	if (IsReload())
	{
		CurrentState = EWeaponState::Reload;
	}
}

void AWeapon::StopReload()
{
	if (CurrentState == EWeaponState::Reload)
	{
		//PlayWeaponSound(ReloadSound);
		bReloading = false;
		CurrentState = EWeaponState::Idle;
	}
}

bool AWeapon::IsFire() const
{
	bool bState = CurrentState == EWeaponState::Idle || CurrentState == EWeaponState::Fire;
	return bState && !bReloading;
}

bool AWeapon::IsReload() const
{
	//bool bState = CurrentState == EWeaponState::Idle || CurrentState == EWeaponState::Fire;
	bool bAmmo = CurrentAmmo <= 0 || CurrentAmmo < MaxAmmo;
	return bAmmo && !bReloading;
}

