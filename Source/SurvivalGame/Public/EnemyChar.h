// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyChar.generated.h"

UCLASS()
class SURVIVALGAME_API AEnemyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Collision")
	USphereComponent* SphereCol;

	bool bInPlayer : 1;

	AActor* CheckActor(FVector EndLoc);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	APawn* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float RunDist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	USoundCue* ExploeSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float ExploeDist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	UParticleSystem* ExploeEffect;

	UPROPERTY()
	UParticleSystemComponent* EffectComp;

	void Explosion();

	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* RunAnim;

private:
	void PlayMontage(UAnimMontage* Anim, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	UAudioComponent* PlaySound(USoundCue* Sound);

	void Die();
};
