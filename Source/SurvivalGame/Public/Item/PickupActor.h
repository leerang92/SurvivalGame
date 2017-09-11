// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UsableActor.h"
#include "ItemInfo.h"
#include "PickupActor.generated.h"

UCLASS()
class SURVIVALGAME_API APickupActor : public AUsableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnUsed(APawn* OwnerPawn) override;

	void OnRespawn();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	FItemInformation ItemInfo;

};
