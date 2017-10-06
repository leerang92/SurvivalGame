// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AI_EnemyController.h"

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	HomeLocation = GetControlledPawn()->GetActorLocation();
}

void AAI_EnemyController::Active(APawn* Target)
{
	if (Target != nullptr)
	{
		MoveToLocation(Target->GetActorLocation(), 150.0f, true, false, true);
	}
}

void AAI_EnemyController::Passive()
{
	StopMovement();

	GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &AAI_EnemyController::ReturnPoint, 3.0f, false);
}

void AAI_EnemyController::ReturnPoint()
{
	MoveToLocation(HomeLocation, 150.0f, true, false, true);
	GetWorld()->GetTimerManager().ClearTimer(WaitTimer);
}
