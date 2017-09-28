// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "EquipActor.generated.h"

UCLASS()
class SURVIVALGAME_API AEquipActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetEqiupWeapon(AWeapon* NewWeapon, FName AttachSlot = TEXT("hand_r"));

	UFUNCTION(BlueprintCallable, Category = "Animation")
	FORCEINLINE bool IsWeapon() const { return FirstWeapon; }

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

private:

	UPROPERTY()
	class AWeapon* FirstWeapon;

	UPROPERTY()
	class AWeapon* SecondWeapon;

	FName HandSocket;
	FName PrimarySocket;
	
};
