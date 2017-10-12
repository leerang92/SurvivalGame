// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIAction.h"
#include "AIAction_Idle.h"
#include "AIAction_Move.h"
#include "AIAction_Attack.h"
#include "AI_EnemyController.h"

AAI_EnemyController::AAI_EnemyController()
{
	AllowedAction.Add(UAIAction_Idle::StaticClass());
	AllowedAction.Add(UAIAction_Move::StaticClass());
	AllowedAction.Add(UAIAction_Attack::StaticClass());
}

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	HomeLocation = GetControlledPawn()->GetActorLocation();
}

void AAI_EnemyController::Active(APawn* Target)
{
	TargetActor = Target;
	/*if (Target != nullptr)
	{
		MoveToLocation(Target->GetActorLocation(), 150.0f, true, false, true);
	}*/
	const int Idx = SelectAction();
	AllAction[Idx]->Active();
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

void AAI_EnemyController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	for (int i = 0; i < AllowedAction.Num(); i++)
	{
		UAIAction* Action = NewObject<UAIAction>(this, AllowedAction[i]);
		check(Action);
		Action->SetController(this);
		AllAction.Add(Action);
	}
}

void AAI_EnemyController::SetStateWeight(const int Index, const float InWeight)
{
	if (Index < 0)
		return;
	
	AllAction[Index]->SetWeight(InWeight);
}

void AAI_EnemyController::DecreaseWeight(const float InWeight)
{
	for (int i = 0; i < AllAction.Num(); ++i)
	{
		AllAction[i]->SetWeight(-InWeight);
	}
	//for(auto& AI : AllAction)
	//{
	//	AI->SetWeight(-InWeight);
	//}
}

int AAI_EnemyController::SelectAction() const
{
	int index = 0;
	for (int i = 1; i < AllAction.Num(); ++i)
	{
		if (AllAction[index]->GetWeight() < AllAction[i]->GetWeight())
		{
			index = i;
		}
	}
	return index;
}
