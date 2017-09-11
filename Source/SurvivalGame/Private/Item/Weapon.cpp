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

	WeaponType = EWeaponType::Rifle;

	bReloading = false;
	bFire = false;

	FireInterval = 0.15f;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->AttachTo(Capsule);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*switch (CurrentState)
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
	}*/
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
		FName AttachPoint = PC->InventoryComp->GetWeaponType(Slot);
		Mesh->AttachToComponent(PC->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
		Mesh->SetRelativeLocation(SetWeaponLocation);
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

void AWeapon::OnFire()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(MyPawn);
	if (PC && IsFire())
	{
		/* 발사 방향 구하기 */
		const FVector CamLoc = PC->FollowCamera->GetComponentLocation();
		const FRotator CamRot = PC->FollowCamera->GetComponentRotation();
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

		CurrentAmmo--;
		if (IsReload())
		{
			OnReload();
		}
	}
}

void AWeapon::OnReload()
{
	if (IsReload()) 
	{
		bReloading = true;
		CurrentState = EWeaponState::Reload;
		// 재장전 애니메이션 재생 후 재장전 완료
		const float Duration = SetAnimation(ReloadAnim);
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AWeapon::FinishReload, Duration, false);

		PlayWeaponSound(ReloadSound);
	}
}

void AWeapon::SetWeaponState()
{	
	if (IsFire()) 
	{
		CurrentState = EWeaponState::Fire;
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeapon::OnFire, FireInterval, true);
	}
	else
	{
		CurrentState = EWeaponState::Idle;
	}
}

void AWeapon::StartFire()
{
	bFire = true;
	SetWeaponState();
}

void AWeapon::StopFire()
{
	bFire = false;
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	SetWeaponState();
}

void AWeapon::FinishReload()
{
	bReloading = false;
	CurrentAmmo = MaxAmmo;
	SetWeaponState();
}

bool AWeapon::IsFire() const
{
	const bool bState = CurrentState == EWeaponState::Idle || CurrentState == EWeaponState::Fire;
	return bState && bFire && !bReloading;
}

bool AWeapon::IsReload() const
{
	//bool bState = CurrentState == EWeaponState::Idle || CurrentState == EWeaponState::Fire;
	const bool bCurrentFire = CurrentState == EWeaponState::Fire && CurrentAmmo <= 0;
	const bool bCurrentIdle = CurrentState == EWeaponState::Idle && CurrentAmmo < MaxAmmo;
	return bCurrentFire || bCurrentIdle && !bReloading;
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

