// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "AI_EnemyController.h"
#include "EnemyChar.h"


// Sets default values
AEnemyChar::AEnemyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RunDist = 350.0f;
	ExploeDist = 150.0f;

	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCol->AttachTo(GetMesh());
	SphereCol->OnComponentBeginOverlap.AddDynamic(this, &AEnemyChar::OnOverlapBegin);

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
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInPlayer)
	{
		AAI_EnemyController* AI = Cast<AAI_EnemyController>(Controller);
		if (TargetActor == CheckActor(TargetActor->GetActorLocation()))
		{	
			AI->Active(TargetActor);
			float Dist = FVector::Distance(TargetActor->GetActorLocation(), GetActorLocation());
			if (Dist < ExploeDist)
			{
				Explosion();
			}
			else if (Dist < RunDist)
			{
				GetCharacterMovement()->MaxWalkSpeed = 500.0f;
			}
		}
		else
		{
			bInPlayer = false;
			AI->Passive();
		}
	}

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

	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, 1.0f, 1.0f);
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECC_WorldStatic, TraceParam);

	return Hit.GetActor();
}

void AEnemyChar::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor == CheckActor(OtherActor->GetActorLocation()))
		{
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

void AEnemyChar::Explosion()
{
	if (ExploeEffect != nullptr && EffectComp == nullptr)
	{
		GetMesh()->SetVisibility(false);
		EffectComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExploeEffect, GetActorLocation());
		PlaySound(ExploeSound);

		TArray<AActor*> IgnoreActor;
		const float Damage = 15.0f;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 150.0f, UDamageType::StaticClass(), IgnoreActor);

		Die();
	}
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
	Destroy();
}

