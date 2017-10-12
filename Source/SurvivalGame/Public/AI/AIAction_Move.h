// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIAction.h"
#include "AIAction_Move.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UAIAction_Move : public UAIAction
{
	GENERATED_BODY()
	
public:
	UAIAction_Move();

	virtual void Active() override;
	
	float NearDist;
};
