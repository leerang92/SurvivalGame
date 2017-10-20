// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIAction.h"

UAIAction::UAIAction() : Weight(1), slope(1)
{
	
}

void UAIAction::Active()
{
	UE_LOG(LogClass, Warning, TEXT("Base Action"));
}

void UAIAction::SetController(AAI_EnemyController* InOwner)
{
	AICon = InOwner;
}

void UAIAction::SetWeight(float InWeight)
{
	Weight += InWeight * slope;
	Weight = FMath::ClampAngle(Weight, 0.0f, 100.0f);
}
