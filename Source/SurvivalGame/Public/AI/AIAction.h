// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AI_EnemyController.h"
#include "AIAction.generated.h"

class AI_EnemyController;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UAIAction : public UObject
{
	GENERATED_BODY()

public:
	UAIAction();

	virtual void Active();

	void SetController(AAI_EnemyController* InOwner);

	FORCEINLINE float GetWeight() const { return Weight; }
	
	void SetWeight(float InWeight);
	
protected:
	TWeakObjectPtr<AAI_EnemyController> AICon;

	float Weight;
};
