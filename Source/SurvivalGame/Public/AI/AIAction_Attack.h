// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIAction.h"
#include "AIAction_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UAIAction_Attack : public UAIAction
{
	GENERATED_BODY()
	
public:
	virtual void Active() override;

	
	
};
