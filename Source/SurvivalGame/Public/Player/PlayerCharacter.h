// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayerState.h"
#include "UsableActor.h"
#include "UserWidget.h"
#include "Inventory.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventory* Inventory;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void FocusActor(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void EndFocusActor(AActor* TargetActor);

protected:

	EPlayerState CurrentState;

	float Yaw;
	float Pitch;

	UPROPERTY(EditAnywhere, Category = "User Interface")
	TSubclassOf<class UUserWidget> PickupUI;

	UPROPERTY()
	class UUserWidget* PickupTooltip;
private:
	/* 카메라 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/* 이동 함수들 */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void TurnRate(float Rate);
	void LookUpAtRate(float Rate);
	void StartCrouch();

	UPROPERTY()
	class AUsableActor* FocusUsableActor;

	bool bHasFocus;

	void PickupItem();

	class AUsableActor* GetUseableItem();

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	EPlayerState GetPlayerState() const { return CurrentState; }
};
