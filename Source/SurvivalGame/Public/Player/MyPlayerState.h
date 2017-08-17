// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "MyPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	PS_Idle		UMETA(DisplayeName = "Idle"),
	PS_Walk		UMETA(DisplayeName = "Walk"),
	PS_Fire		UMETA(DisplayeName = "Fire"),
	PS_Reload	UMETA(DisplayeName = "Reload"),
	PS_Crouch	UMETA(DisplayeName = "Crouch"),
};