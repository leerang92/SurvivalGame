// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "WeaponType.h"
#include "UIInventory.h"
#include "UserWidget.h"
#include "ItemInfo.h"
#include "MainHUD.h"
#include "Inventory.generated.h"

USTRUCT()
struct FWeaponSlot
{
	GENERATED_BODY()

	UPROPERTY()
	class AWeapon* First;

	UPROPERTY()
	class AWeapon* Second;

	UPROPERTY()
	class AWeapon* Auxiliary;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UInventory();

	// �÷��̾� Pawn ����
	void SetOwnerPawn(APawn* OwnerPawn);

	// �κ��丮�� ���� �߰�
	void AddWeapon(class AWeapon* NewWeapon);

	void AddItem(FItemInformation NewItem);

	// ���� Ÿ�Կ� ���� ���� ����Ʈ ��ȯ
	FName GetWeaponType(const EWeaponSlot GetSlot) const;

	// ���� ������
	void DropItem();

	// ���� ��ü
	void SwapWeapon(const int Index);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE class AWeapon* GetCurrentWeapon() const { 
		return CurrentWeapon; 
	}

	void CreateUI();

	void SetInventoryUI(bool bShow);

protected:
	// �ֹ��� ����
	void SetCurrentWeapon(AWeapon* NewWeapon, AWeapon* LastWeapon);

	void FinishSwapWeapon();

	// ���� �迭���� ���� ���� ������ ����
	void RemoveWeapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Slot")
	int WeaponSlotNum;

	// ���� �������� ����
	UPROPERTY()
	class AWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InvenClass;

	UPROPERTY()
	class UUIInventory* InvenUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	class UMainHUD* MainHUD;

protected:
	// ���� �迭
	UPROPERTY()
	TArray<AWeapon*> WeaponList;

	// ������ ����
	EWeaponSlot Slot;

private:
	UPROPERTY()
	class APawn* MyPawn;

	FTimerHandle SwapTimerHandle;

	/* ���� ������ ���� �̸��� */
	FName AttachHand;
	FName AttachPrimary;
	FName AttachSecondery;

};
