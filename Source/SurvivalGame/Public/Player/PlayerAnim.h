// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "PlayerCharacter.h"
#include "WeaponRifle.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void AnimNotify_CreateClip(UAnimNotify* Notify);
	
	UFUNCTION()
	void AnimNotify_AttachClip(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_Equip(UAnimNotify* Notify);
};
