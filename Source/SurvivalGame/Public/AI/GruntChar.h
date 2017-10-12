// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyChar.h"
#include "GruntChar.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AGruntChar : public AEnemyChar
{
	GENERATED_BODY()
	
public:

	AGruntChar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float speed;

	void Explosion();

protected:

	/* 폭발 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float RunDist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float ExploeDist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float ExploeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	USoundCue* ExploeSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	UParticleSystem* ExploeEffect;

	UPROPERTY()
	UParticleSystemComponent* EffectComp;


	// 애니메이션
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* RunAnim;
	
};
