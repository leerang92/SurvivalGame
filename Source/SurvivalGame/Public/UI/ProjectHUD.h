// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ProjectHUD.generated.h"

UENUM()
enum ECrossHairDirection
{
	Center,
	Top,
	Bottom,
	Left,
	Right,
};

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AProjectHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AProjectHUD();

	void DrawHUD();

	void DrawCrossHair();

	void DrawAlignedIconWithPerfectPixel(const FCanvasIcon& pIcon, const int pX, const int pY,
		const ECrossHairDirection pAlign, const float pScale = 1.0f);

public:
	UPROPERTY()
	TArray<FCanvasIcon> CrossHairIcon;

protected:

	ECrossHairDirection CrossHairDir;
};
