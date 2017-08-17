// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UsableActor.generated.h"

UCLASS()
class SURVIVALGAME_API AUsableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableActor();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnBeginFocus();

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnEndFocus();

	virtual void OnUsed(APawn* Owner);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	
};
