// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "GruntChar.h"

AGruntChar::AGruntChar()
{
	RunDist = 1500.0f;
	ExploeDist = 150.0f;
	ExploeDamage = 30.0f;

	speed = 1.0f;
}

void AGruntChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (TargetActor)
	{
		const float Dist = FVector::Distance(TargetActor->GetActorLocation(), GetActorLocation());
		if (Dist < ExploeDist)
		{
			AICon->SetStateWeight(EEnemyState::ATTACK, 10.0f);
		}
	}*/
}

void AGruntChar::Explosion()
{
	if (ExploeEffect != nullptr && EffectComp == nullptr)
	{
		//GetMesh()->SetVisibility(false);
		EffectComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExploeEffect, GetActorLocation());
		PlaySound(ExploeSound);

		TArray<AActor*> IgnoreActor;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), ExploeDamage, GetActorLocation(), 300.0f, UDamageType::StaticClass(), IgnoreActor);

		//AActor* Target = Cast<AActor>(TargetActor);

		//TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		//FDamageEvent DamageEvent(ValidDamageTypeClass);
		//AAI_EnemyController* AI = Cast<AAI_EnemyController>(Controller);
		//Target->TakeDamage(15.0f, DamageEvent, AI, this);

		Eliminate();
	}
}
