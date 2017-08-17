// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasFocus = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Yaw = 0.0f;
	Pitch = 0.0f;

	UIPickup = CreateWidget<UUserWidget>(GetWorld(), PickupUI);
	UIPickup->AddToViewport();
	UIPickup->SetVisibility(ESlateVisibility::Hidden);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller) 
	{
		AUsableActor* UsableActor = GetUseableItem();
		//UE_LOG(LogClass, Warning, TEXT("%s"), *UsableActor->GetName());
		if (FocusUsableActor != UsableActor)
		{
			if (FocusUsableActor)
			{
				UE_LOG(LogClass, Warning, TEXT("!"));
				FocusUsableActor->OnEndFocus();
				UIPickup->SetVisibility(ESlateVisibility::Hidden);
			}
			bHasFocus = true;
		}

		FocusUsableActor = UsableActor;

		if (FocusUsableActor)
		{
			if(bHasFocus)
			FocusUsableActor->OnBeginFocus();
			UIPickup->SetVisibility(ESlateVisibility::Visible);
			bHasFocus = false;
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);

	InputComponent->BindAction("Pickup", IE_Pressed, this, &APlayerCharacter::PickupItem);
}

void APlayerCharacter::FocusActor(AActor * TargetActor)
{
	if (TargetActor) {
		AUsableActor* Item = Cast<AUsableActor>(TargetActor);
		Item->MeshComp->SetVisibility(false);
	}
}

void APlayerCharacter::EndFocusActor(AActor * TargetActor)
{
	if (TargetActor) {
		AUsableActor* Item = Cast<AUsableActor>(TargetActor);
		Item->MeshComp->SetVisibility(true);
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::StartSprint()
{
	if (GetVelocity().Size() > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}
}

void APlayerCharacter::StopSprint()
{
	if (GetVelocity().Size() > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void APlayerCharacter::TurnRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	FRotator Rotation = Controller->GetControlRotation() - GetActorRotation();
	FRotator CurrentRot = FRotator(Pitch, Yaw, 0);
	FRotator InterRot = FMath::RInterpTo(CurrentRot, Rotation, GetWorld()->DeltaTimeSeconds, 15.0f);

	//if (InterRot.Yaw < -12.0f)
	//{
	//	FRotator SetRot;
	//	SetRot.Yaw -= 1;
	//	SetActorRotation(SetRot);
	//}
	//else if (InterRot.Yaw > 12.0f)
	//{
	//	FRotator SetRot;
	//	SetRot.Yaw += 1;
	//	SetActorRotation(SetRot);
	//}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::StartCrouch()
{
	if (CurrentState != EPlayerState::PS_Crouch) {
		CurrentState = EPlayerState::PS_Crouch;
	}
	else if (CurrentState == EPlayerState::PS_Crouch) {
		CurrentState = EPlayerState::PS_Idle;
	}
}

void APlayerCharacter::PickupItem()
{
	//AUsableActor* 
}

AUsableActor * APlayerCharacter::GetUseableItem()
{
	FVector CamLoc = FVector::ZeroVector;
	FRotator CamRot = FRotator::ZeroRotator;

	if (Controller == nullptr)
		return nullptr;

	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector StartTrace = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector EndTrace = StartTrace + (Direction * 500.0f);

	FCollisionQueryParams TraceParam(TEXT("TraceUsableActor"), true, this);
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;

	TraceParam.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, TraceParam);

	return Cast<AUsableActor>(Hit.GetActor());
}

