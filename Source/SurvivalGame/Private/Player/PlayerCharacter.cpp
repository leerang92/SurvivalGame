// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PickupWeapon.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasFocus = true;
	IsZoom = false;
	IsInventory = false;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryComp->SetOwnerPawn(this);
	InventoryComp->CreateUI();

	PickupTooltip = CreateWidget<UUserWidget>(GetWorld(), PickupUI);
	PickupTooltip->AddToViewport();
	PickupTooltip->SetVisibility(ESlateVisibility::Hidden);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller) 
	{
		AUsableActor* UsableActor = GetUseableItem();
		if (FocusUsableActor != UsableActor)
		{
			if (FocusUsableActor)
			{
				FocusUsableActor->OnEndFocus();
				PickupTooltip->SetVisibility(ESlateVisibility::Hidden);
			}
			bHasFocus = true;
		}

		FocusUsableActor = UsableActor;

		if (FocusUsableActor)
		{
			if(bHasFocus)
			FocusUsableActor->OnBeginFocus();
			PickupTooltip->SetVisibility(ESlateVisibility::Visible);
			bHasFocus = false;
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* 이동 */
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);

	/* 무기 발사, 재장전 */
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::StartReload);

	InputComponent->BindAction("Zoom", IE_Pressed, this, &APlayerCharacter::ZoomIn);
	InputComponent->BindAction("Zoom", IE_Released, this, &APlayerCharacter::ZoomOut);

	/* 아이템 줍기, 버리기*/
	InputComponent->BindAction("Pickup", IE_Pressed, this, &APlayerCharacter::PickupItem);
	InputComponent->BindAction("DropItem", IE_Pressed, this, &APlayerCharacter::DropItem);

	/* 무기 교체 */
	InputComponent->BindAction("SwapWeapon1", IE_Pressed, this, &APlayerCharacter::SwapWeapon<0>);
	InputComponent->BindAction("SwapWeapon2", IE_Pressed, this, &APlayerCharacter::SwapWeapon<1>);

	InputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::ShowInventory);
}

FRotator APlayerCharacter::GetAimOffset(float AimPitch, float AimYaw)
{
	FRotator LookRot = GetControlRotation() - GetActorRotation();
	LookRot.Normalize();

	FRotator InterRot = FMath::RInterpTo(FRotator(AimPitch, AimYaw, 0), LookRot, GetWorld()->GetDeltaSeconds(), 0.0f);

	AimPitch = FMath::ClampAngle(InterRot.Pitch, -90.0f, 90.0f);
	AimYaw = FMath::ClampAngle(InterRot.Yaw, -90.0f, 90.0f);

	return FRotator(AimPitch, AimYaw, 0);
}

void APlayerCharacter::ZoomIn()
{
	if (InventoryComp->GetCurrentWeapon()) 
	{
		IsZoom = true;
		FollowCamera->FieldOfView = 60.0f;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void APlayerCharacter::ZoomOut()
{
	IsZoom = false;
	FollowCamera->FieldOfView = 90.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::MoveForward(float Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value);
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
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	/*AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	FRotator Rotation = Controller->GetControlRotation() - GetActorRotation();
	FRotator CurrentRot = FRotator(Pitch, Yaw, 0);
	FRotator InterRot = FMath::RInterpTo(CurrentRot, Rotation, GetWorld()->DeltaTimeSeconds, 15.0f);*/
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

void APlayerCharacter::StartFire()
{
	if (InventoryComp->GetCurrentWeapon() != nullptr) 
	{
		InventoryComp->GetCurrentWeapon()->StartFire();
	}
}

void APlayerCharacter::StopFire()
{
	if (InventoryComp->GetCurrentWeapon() != nullptr)
		InventoryComp->GetCurrentWeapon()->StopFire();
}

void APlayerCharacter::StartReload()
{
	if (InventoryComp->GetCurrentWeapon() != nullptr)
	{
		InventoryComp->GetCurrentWeapon()->OnReload();
	}
}

void APlayerCharacter::PickupItem()
{
	if (FocusUsableActor)
	{
		FocusUsableActor->OnUsed(this);
	}
}

void APlayerCharacter::DropItem()
{
	InventoryComp->DropItem();
}

template<int Value>
void APlayerCharacter::SwapWeapon()
{
	InventoryComp->SwapWeapon(Value);
}

AUsableActor * APlayerCharacter::GetUseableItem()
{
	if (Controller == nullptr)
		return nullptr;

	FVector CamLoc = FVector::ZeroVector;
	FRotator CamRot = FRotator::ZeroRotator;

	// 플레이어가 봐라보는 방향
	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector StartTrace = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector EndTrace = StartTrace + (Direction * 500.0f);

	// 트레이스 발사
	FCollisionQueryParams TraceParam(TEXT("TraceUsableActor"), true, this);
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;

	TraceParam.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, TraceParam);

	return Cast<AUsableActor>(Hit.GetActor());
}

void APlayerCharacter::ShowInventory()
{
	if (!IsInventory)
	{
		InventoryComp->SetInventoryUI(true);
		IsInventory = true;
	}
	else
	{
		InventoryComp->SetInventoryUI(false);
		IsInventory = false;
	}
}

