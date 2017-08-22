// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "WeaponType.h"
#include "Inventory.generated.h"

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

	// �ֹ��� ����
	void SetCurrentWeapon(AWeapon* NewWeapon);

	// ���� Ÿ�Կ� ���� ���� ����Ʈ ��ȯ
	FName GetWeaponType(EWeaponSlot GetSlot) const;

	class AWeapon* CurrentWeapon;

	class AWeapon* SeconderyWeapon;

	void RemoveWeapon();


protected:

	EWeaponSlot Slot;

	// Called when the game starts
	virtual void BeginPlay() override;

	void EquipWeapon(class AWeapon* NewWeapon);


	TArray<AWeapon*> WeaponList;

private:
	class APawn* MyPawn;

	FName AttachHand;
	FName AttachPrimary;
	FName AttachSecondery;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int WeaponSlotNum;
};
