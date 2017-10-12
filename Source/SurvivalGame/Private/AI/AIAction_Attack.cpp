// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "GruntChar.h"
#include "AIAction_Attack.h"


void UAIAction_Attack::Active()
{
	UE_LOG(LogClass, Warning, TEXT("Attack"));

	AGruntChar* const Grunt = Cast<AGruntChar>(AICon->GetControlledPawn());
	if (Grunt)
	{
		Grunt->Explosion();
	}
}

