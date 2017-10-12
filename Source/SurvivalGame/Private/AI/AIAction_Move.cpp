// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIAction_Move.h"


UAIAction_Move::UAIAction_Move()
{
	NearDist = 2000.0f;
}

void UAIAction_Move::Active()
{
	if (AICon->TargetActor == nullptr)
		return;

	UE_LOG(LogClass, Warning, TEXT("Move"));
	const FVector TargetLocation = AICon->TargetActor->GetActorLocation();

	const float Dist = FVector::Distance(TargetLocation, AICon->GetControlledPawn()->GetActorLocation());
	if (Dist < 1100.0f)
	{
		ACharacter* Pawn = Cast<ACharacter>(AICon->GetControlledPawn());
		Pawn->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}

	AICon->MoveToLocation(TargetLocation, 150.0f, true, false, true);

	//float Dist = FVector::Distance(TargetLocation, AICon->GetControlledPawn()->GetActorLocation());
	//if (Dist > 2000.0f)
	//{
	//	SetWeight(-1.0f);
	//	AICon->SetStateWeight(0, 1.0f);
	//}
}

