// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "ProjectHUD.h"

AProjectHUD::AProjectHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture> CrossHairTex(TEXT("Texture2D'/Game/Image/CrossHair.CrossHair'"));
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 16, 6, 6)); // Áß¾Ó
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 24, 6, 25)); // À§
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 8, 24, 6, 25)); // ¾Æ·¡
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 0, 25, 6)); // ¿ÞÂÊ
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 8, 25, 6)); // ¿À¸¥ÂÊ

}

void AProjectHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AProjectHUD::DrawCrossHair()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwningPlayerController());

		int CorssHairSpred = 10;
		const int Width = static_cast<int>(Canvas->ClipX);
		const int Height = static_cast<int>(Canvas->ClipY);
		const int CenterX = Width / 2;
		const int CenterY = Height / 2;

		Canvas->SetDrawColor(FColor::White);
		for (int32 i = 0; i < CrossHairIcon.Num(); ++i)
		{
			int CanvasX = 0, CanvasY = 0;
			switch (i)
			{
			case ECrossHairDirection::Top:
				CanvasY -= CorssHairSpred;
				break;
			case ECrossHairDirection::Bottom:
				CanvasY = CorssHairSpred;
				break;
			case ECrossHairDirection::Left:
				CanvasX -= CorssHairSpred;
				break;
			case ECrossHairDirection::Right:
				CanvasX = CorssHairSpred;
				break;
			}
			DrawAlignedIconWithPerfectPixel(CrossHairIcon[i], CenterX + CanvasX, CenterY + CanvasY, static_cast<ECrossHairDirection>(i), 0.5f);
		}
	
}

void AProjectHUD::DrawAlignedIconWithPerfectPixel(const FCanvasIcon & pIcon, const int pX, const int pY, const ECrossHairDirection pAlign, const float pScale)
{
	const int lWidth = static_cast<int>(pIcon.UL), lHeight = static_cast<int>(pIcon.VL);
	int lX = -lWidth / 2, lY = -lHeight / 2;
	switch (pAlign)
	{
	case ECrossHairDirection::Top:
		lY = -lHeight * pScale;
		break;
	case ECrossHairDirection::Bottom:
		lY = 0;
		break;
	case ECrossHairDirection::Left:
		lX = -lWidth * pScale;
		break;
	case ECrossHairDirection::Right:
		lX = 0;
		break;
	}
	Canvas->DrawIcon(pIcon, pX + lX, pY + lY, pScale);
}
