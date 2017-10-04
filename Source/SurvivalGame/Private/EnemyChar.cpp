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

	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCol->AttachTo(GetMesh());
	SphereCol->OnComponentBeginOverlap.AddDynamic(this, &AEnemyChar::OnOverlapBegin);

	GetCharacterMovement()->UpdatedComponent = GetCapsuleComponent();
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
		AI->MoveToLocation(TargetActor->GetActorLocation(), 150.0f, true, false, true);
		UE_LOG(LogClass, Warning, TEXT("Move"));
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
	GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECC_Camera, TraceParam);

	return Hit.GetActor();
}

void AEnemyChar::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{

		if (OtherActor == CheckActor(OtherActor->GetActorLocation()))
		{
			bInPlayer = true;
			TargetActor = OtherActor;
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

