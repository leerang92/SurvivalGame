// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_EnemyController.h"
#include "EnemyChar.generated.h"

enum EEnemyState
{
	IDLE,
	MOVE,
	ATTACK,
};

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

	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHitOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsDie;

protected:

	APawn* TargetActor;

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* DeathAnim;

	UAudioComponent* AudioComp;

	UAudioComponent* PlaySound(USoundCue* Sound);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHP;

	float CurrentHP;

	void PlayMontage(UAnimMontage* Anim, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	void Die();

	void Eliminate();

	class AAI_EnemyController* AICon;

	void SetState();

	FTimerHandle LoopTimerHandle;

	float CountDown;
};
