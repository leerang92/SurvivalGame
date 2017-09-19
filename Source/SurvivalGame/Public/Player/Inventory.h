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

	// 플레이어 Pawn 설정
	void SetOwnerPawn(APawn* OwnerPawn);

	// 인벤토리에 무기 추가
	void AddWeapon(class AWeapon* NewWeapon);

	void AddItem(FItemInformation NewItem);

	// 무기 타입에 따른 장착 포인트 반환
	FName GetWeaponType(const EWeaponSlot GetSlot) const;

	// 무기 버리기
	void DropItem();

	// 무기 교체
	void SwapWeapon(const int Index);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE class AWeapon* GetCurrentWeapon() const { 
		return CurrentWeapon; 
	}

	void CreateUI();

	void SetInventoryUI(bool bShow);

protected:
	// 주무기 장착
	void SetCurrentWeapon(AWeapon* NewWeapon, AWeapon* LastWeapon);

	void FinishSwapWeapon();

	// 무기 배열에서 버린 무기 데이터 삭제
	void RemoveWeapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Slot")
	int WeaponSlotNum;

	// 현재 장착중인 무기
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
	// 무기 배열
	UPROPERTY()
	TArray<AWeapon*> WeaponList;

	// 장착할 슬롯
	EWeaponSlot Slot;

private:
	UPROPERTY()
	class APawn* MyPawn;

	FTimerHandle SwapTimerHandle;

	/* 무기 장착할 소켓 이름들 */
	FName AttachHand;
	FName AttachPrimary;
	FName AttachSecondery;

};
