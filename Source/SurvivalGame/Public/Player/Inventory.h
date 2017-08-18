// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddWeapon(class AWeapon* NewWeapon);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<AWeapon*> WeaponList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int WeaponSlotNum;
};
