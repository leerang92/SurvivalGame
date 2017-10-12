// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "EnemyChar.h"


// Sets default values
AEnemyChar::AEnemyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	CountDown = 0.0f;

	IsDie = false;

	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCol->AttachTo(GetMesh());
	SphereCol->OnComponentBeginOverlap.AddDynamic(this, &AEnemyChar::OnOverlapBegin);
	SphereCol->OnComponentEndOverlap.AddDynamic(this, &AEnemyChar::OnOverlapEnd);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyChar::OnHitOverlapBegin);

	GetCharacterMovement()->UpdatedComponent = GetCapsuleComponent();
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanWalk = true;
	GetCharacterMovement()->SetJumpAllowed(true);
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bAlwaysCheckFloor = false;

	AIControllerClass = AAI_EnemyController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyChar::BeginPlay()
{
	Super::BeginPlay();
	AICon = Cast<AAI_EnemyController>(Controller);

	//GetWorldTimerManager().SetTimer(LoopTimerHandle, this, &AEnemyChar::SetState, 0.2f, true);
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AICon->Active(TargetActor);
	if (AICon)
	{
		if (TargetActor != nullptr && CurrentHP > 0.0f)
		{
			AICon->Active(TargetActor);
		}
		else
		{
			AICon->Passive();
		}
	}
	SetState();
	//CountDown += DeltaTime;
	//if (CountDown > 0.5f)
	//{
	//	SetState();
	//	CountDown = 0.0f;
	//}
}

// Called to bind functionality to input
void AEnemyChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor * AEnemyChar::CheckActor(FVector EndLoc)
{
	FCollisionQueryParams TraceParam(TEXT("CheckCharacter"), true, this);
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;
	TraceParam.bTraceComplex = true;

	const FVector StartLoc = GetActorLocation();

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECC_WorldStatic, TraceParam);

	return Hit.GetActor();
}

void AEnemyChar::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter* const PC = Cast<APlayerCharacter>(OtherActor);
		if (PC && OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			//AICon->SetStateWeight(static_cast<int>(EEnemyState::MOVE), 2.0f);
			bInPlayer = true;
			TargetActor = Cast<APawn>(OtherActor);
		}

	/*	const FVector Start = GetActorLocation();
		const FVector End = Start + 15.0f;

		DrawDebugSphere(GetWorld(), Start, 500.0f, 1, FColor::Red, 1.0f, 1.0f);

		TArray<FHitResult> Hit;
		GetWorld()->SweepMultiByObjectType(Hit, Start, End, FQuat::Identity, 0, FCollisionShape::MakeSphere(500.0f), FCollisionQueryParams::FCollisionQueryParams(false));

		if (Hit.Num() > 0)
		{
			for (int i = 0; i< Hit.Num(); ++i)
				UE_LOG(LogClass, Warning, TEXT("%s"), *Hit[i].GetActor()->GetName());
		}*/
	}
}

void AEnemyChar::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter* const PC = Cast<APlayerCharacter>(OtherActor);
		if (PC)
		{
			bInPlayer = false;
		}
	}
}

void AEnemyChar::OnHitOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);
		if (Projectile)
		{
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			TakeDamage(Projectile->GetDamage(), DamageEvent, GetController(), this);
		}
	}
}

float AEnemyChar::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		CurrentHP -= ActualDamage * 0.5f;

		if (CurrentHP <= 0.0f)
		{
			Die();
		}
	}
	return ActualDamage;
}

void AEnemyChar::PlayMontage(UAnimMontage * Anim, float InPlayRate, FName StartSelectName)
{
	PlayAnimMontage(Anim, InPlayRate, StartSelectName);
}

UAudioComponent * AEnemyChar::PlaySound(USoundCue * Sound)
{
	if (!Sound)
		return nullptr;

	UAudioComponent* AC;
	AC = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, GetActorLocation());

	return AC;
}

void AEnemyChar::Die()
{
	CurrentHP = FMath::Min(0.0f, CurrentHP);

	IsDie = true;
	//AICon = nullptr;
	//if (GetCharacterMovement())
	//{
	//	GetCharacterMovement()->StopMovementImmediately();
	//	GetCharacterMovement()->DisableMovement();
	//}
	//if (DeathAnim) 
	//{
	//	PlayMontage(DeathAnim);
	//	UAnimInstance * AnimInstance = nullptr;
	//}
	//

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyChar::Eliminate, 60.0f, false);

	//OnDestroy();
}

void AEnemyChar::Eliminate()
{
	SetLifeSpan(0.001f);
}

void AEnemyChar::SetState()
{
	if (TargetActor != nullptr)
	{
		const float Dist = FVector::Distance(TargetActor->GetActorLocation(), GetActorLocation());
		if (bInPlayer)
		{
			if (Dist < 150.0f)
			{
				AICon->SetStateWeight(EEnemyState::ATTACK, 100.0f);
			}
			else if (Dist < 1500.0f)
			{
				AICon->SetStateWeight(EEnemyState::MOVE, 50.0f);
			}
		}
		else if (!bInPlayer && Dist > 2000.0f)
		{
			AICon->SetStateWeight(EEnemyState::IDLE, 10.0f);
		}
	}
	AICon->DecreaseWeight(10.0f);
}

