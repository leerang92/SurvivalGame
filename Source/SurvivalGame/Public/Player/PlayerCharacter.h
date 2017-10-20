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

	// 발사 가능 여부
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
	// 무기 교체
	template<int Value>
	void SwapWeapon();

	// 무기 줌 인/아웃
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

	/* UI 생성 여부 */
	bool IsInventory;
	bool IsEquip;

	/* 메인 HUD 클래스 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> MainHUDClass;

	class UMainHUD* MainHUD;

	/* 장비창에 사용 될 캐릭터 액터 */
	UPROPERTY(EditAnywhere, Category = "Equip Character")
	TSubclassOf<class AActor> EquipCharacterClass;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Character")
	class AEquipActor* EquipCharacter;

protected:
	// 현재 상태
	EPlayerState CurrentState;

private:

	/* 이동 함수들 */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void TurnRate(float Rate);
	void LookUpAtRate(float Rate);
	void StartCrouch();

	/* 무기 발사, 중지, 재장전 */
	void StartFire();
	void StopFire();
	void StartReload();

	// 포커싱 된 액터
	UPROPERTY()
	class AUsableActor* FocusUsableActor;

	bool bHasFocus;

	/* 아이템 줍기 버리기 */
	void PickupItem();

	void DropItem();

	// 아이템 찾기
	class AUsableActor* GetUseableItem();

	/* UI */
	void ShowInventory();

	void ShowEquipment();

	/* 체력 */
	float MaxHP;

	float CurrentHP;

};
