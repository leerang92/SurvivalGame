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

	const int Idx = SelectAction();
	AllAction[Idx]->Active();
}

void AAI_EnemyController::Passive()
{
	StopMovement();

	GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &AAI_EnemyController::ReturnPoint, 3.0f, false);
}

void AAI_EnemyController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	// 상태 클래스들을 각각 AIAction으로 형변환 후 배열에 저장
	for (auto &AllowedAction : AllowedAction)
	{
		UAIAction* Action = NewObject<UAIAction>(this, AllowedAction);
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
	// 모든 상태의 가중치 감소
	for (auto &Action : AllAction)
	{
		Action->SetWeight(-InWeight);
	}
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
