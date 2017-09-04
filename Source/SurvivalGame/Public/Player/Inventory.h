// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "WeaponType.h"
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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �÷��̾� Pawn ����
	void SetOwnerPawn(APawn* OwnerPawn);

	// �κ��丮�� ���� �߰�
	void AddWeapon(class AWeapon* NewWeapon);

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

protected:
	virtual void BeginPlay() override;

	// �ֹ��� ����
	void SetCurrentWeapon(AWeapon* NewWeapon, AWeapon* LastWeapon);

	// ���� �迭���� ���� ���� ������ ����
	void RemoveWeapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Slot")
	int WeaponSlotNum;

	// ���� �������� ����
	UPROPERTY()
		class AWeapon* CurrentWeapon;

protected:
	// ���� �迭
	UPROPERTY()
	TArray<AWeapon*> WeaponList;

	// ������ ����
	EWeaponSlot Slot;

private:
	UPROPERTY()
	class APawn* MyPawn;



	/* ���� ������ ���� �̸��� */
	FName AttachHand;
	FName AttachPrimary;
	FName AttachSecondery;

};
