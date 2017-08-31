// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponClip.generated.h"

UCLASS()
class SURVIVALGAME_API AWeaponClip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponClip();

	void OnEquip(USceneComponent* InParent, FName AttachPoint = TEXT("ClipSocket"));

	void OnUnEquip();

private:
	void OnDestroy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Clip")
	float LifeTime;

private:

	FTimerHandle DestoryTimerHandle;
	
	
};
