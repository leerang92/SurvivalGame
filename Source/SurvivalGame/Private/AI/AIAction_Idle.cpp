// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIAction_Idle.h"


void UAIAction_Idle::Active()
{
	UE_LOG(LogClass, Warning, TEXT("Idle"));

	AICon->MoveToLocation(AICon->HomeLocation, 1.0f);
}

