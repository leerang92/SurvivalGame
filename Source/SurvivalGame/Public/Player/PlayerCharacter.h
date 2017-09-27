// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayerState.h"
#include "UsableActor.h"
#include "UserWidget.h"
#include "Inventory.h"
#include "MainHUD.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SURVIVALGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "State")
	EPlayerState GetPlayerState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetIsFire() const;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	FRotator GetAimOffset(float AimPitch, float AimYaw);

protected:

	UPROPERTY()
	class UUserWidget* PickupTooltip;

	template<int Value>
	void SwapWeapon();

	void ZoomIn();
	void ZoomOut();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventory* InventoryComp;

	/* 카메라 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	bool IsZoom;

	bool IsInventory;
	bool IsEquip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> MainHUDClass;

	class UMainHUD* MainHUD;

protected:
	// 현재 상태
	EPlayerState CurrentState;

	UPROPERTY(EditAnywhere, Category = "User Interface")
	TSubclassOf<class UUserWidget> PickupUI;


private:

	/* 이동 함수들 */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void TurnRate(float Rate);
	void LookUpAtRate(float Rate);
	void StartCrouch();

	void StartFire();
	void StopFire();
	void StartReload();

	UPROPERTY()
	class AUsableActor* FocusUsableActor;

	bool bHasFocus;

	void PickupItem();

	void DropItem();

	class AUsableActor* GetUseableItem();

	void ShowInventory();

	void ShowEquipment();

};
