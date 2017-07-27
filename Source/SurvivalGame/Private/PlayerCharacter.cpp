// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponSkelMesh(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->AttachTo(GetMesh(), TEXT("WeaponSocket"));
	WeaponMesh->SetSkeletalMesh(WeaponSkelMesh.Object);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Yaw = 0.0f;
	Pitch = 0.0f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
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

void APlayerCharacter::TurnRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	FRotator Rotation = Controller->GetControlRotation() - GetActorRotation();
	FRotator CurrentRot = FRotator(Pitch, Yaw, 0);
	FRotator InterRot = FMath::RInterpTo(CurrentRot, Rotation, GetWorld()->DeltaTimeSeconds, 15.0f);

	if (InterRot.Yaw < -12.0f)
	{
		FRotator SetRot;
		SetRot.Yaw -= 1;
		SetActorRotation(SetRot);
	}
	else if (InterRot.Yaw > 12.0f)
	{
		FRotator SetRot;
		SetRot.Yaw += 1;
		SetActorRotation(SetRot);
	}
	UE_LOG(LogClass, Warning, TEXT("%f"), InterRot.Yaw);
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

