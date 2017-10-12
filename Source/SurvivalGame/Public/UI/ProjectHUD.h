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

	UPROPERTY()
	FCanvasIcon HealthBar;
	UPROPERTY()
	FCanvasIcon HealthBarBg;
	UPROPERTY()
	FCanvasIcon HealthIcon;

	void DrawHP();

public:
	UPROPERTY()
	TArray<FCanvasIcon> CrossHairIcon;

	UTexture2D* HUDTexture;

protected:

	ECrossHairDirection CrossHairDir;

	void MakeUV(FCanvasIcon & Icon, FVector2D & UV0, FVector2D & UV1, uint16 U, uint16 V, uint16 UL, uint16 VL);
};
