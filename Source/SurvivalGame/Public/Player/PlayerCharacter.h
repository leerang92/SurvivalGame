// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayerState.h"
#include "UsableActor.h"
#include "UserWidget.h"
#include "Inventory.h"
#include "MainHUD.h"
#include "EquipActor.h"
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

	// �߻� ���� ����
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetIsFire() const;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	FRotator GetAimOffset(float AimPitch, float AimYaw);

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetMaxHP() const { return MaxHP; }

protected:
	// ���� ��ü
	template<int Value>
	void SwapWeapon();

	// ���� �� ��/�ƿ�
	void ZoomIn();
	void ZoomOut();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventory* InventoryComp;

	/* ī�޶� */
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

	/* UI ���� ���� */
	bool IsInventory;
	bool IsEquip;

	/* ���� HUD Ŭ���� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> MainHUDClass;

	class UMainHUD* MainHUD;

	/* ���â�� ��� �� ĳ���� ���� */
	UPROPERTY(EditAnywhere, Category = "Equip Character")
	TSubclassOf<class AActor> EquipCharacterClass;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Character")
	class AEquipActor* EquipCharacter;

protected:
	// ���� ����
	EPlayerState CurrentState;

private:

	/* �̵� �Լ��� */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void TurnRate(float Rate);
	void LookUpAtRate(float Rate);
	void StartCrouch();

	/* ���� �߻�, ����, ������ */
	void StartFire();
	void StopFire();
	void StartReload();

	// ��Ŀ�� �� ����
	UPROPERTY()
	class AUsableActor* FocusUsableActor;

	bool bHasFocus;

	/* ������ �ݱ� ������ */
	void PickupItem();

	void DropItem();

	// ������ ã��
	class AUsableActor* GetUseableItem();

	/* UI */
	void ShowInventory();

	void ShowEquipment();

	/* ü�� */
	float MaxHP;

	float CurrentHP;

};
