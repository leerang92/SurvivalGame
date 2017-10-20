// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_EnemyController.generated.h"

class UAIAction;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAI_EnemyController();

	virtual void BeginPlay() override;

	void Active(APawn* Target);

	void Passive();

	FTimerHandle WaitTimer;

	FVector HomeLocation;

public:
	virtual void Possess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIController")
	TArray<TSubclassOf<UAIAction>> AllowedAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIController")
	TArray<UAIAction*> AllAction;

	void SetStateWeight(const int Index, const float InWeight);

	void DecreaseWeight(const float InWeight);

	class AActor* TargetActor;

protected:

	int SelectAction() const;
};
