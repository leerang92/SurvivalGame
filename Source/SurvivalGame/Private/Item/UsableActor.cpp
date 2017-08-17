// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "UsableActor.h"


// Sets default values
AUsableActor::AUsableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AUsableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUsableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUsableActor::OnBeginFocus()
{
	MeshComp->SetRenderCustomDepth(true);
}

void AUsableActor::OnEndFocus()
{
	MeshComp->SetRenderCustomDepth(false);
}

void AUsableActor::OnUsed(APawn* Owner)
{
}

