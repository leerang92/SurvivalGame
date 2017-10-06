// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	void Active(APawn* Target);

	void Passive();

	FTimerHandle WaitTimer;

	FVector HomeLocation;

	void ReturnPoint();
};
