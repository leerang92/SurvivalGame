// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PlayerCharacter.h"
#include "ProjectHUD.h"

AProjectHUD::AProjectHUD()
{

	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDTextureObj(TEXT("Texture2D'/Game/UI/HUD/HUDAssets02.HUDAssets02'"));

	static ConstructorHelpers::FObjectFinder<UTexture> CrossHairTex(TEXT("Texture2D'/Game/Image/CrossHair.CrossHair'"));
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 16, 6, 6)); // Áß¾Ó
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 24, 6, 25)); // À§
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 8, 24, 6, 25)); // ¾Æ·¡
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 0, 25, 6)); // ¿ÞÂÊ
	CrossHairIcon.Add(UCanvas::MakeIcon(CrossHairTex.Object, 0, 8, 25, 6)); // ¿À¸¥ÂÊ

	HUDTexture = HUDTextureObj.Object;
	HealthBar = UCanvas::MakeIcon(HUDTexture, 67, 212, 372, 50);
	HealthBarBg = UCanvas::MakeIcon(HUDTexture, 67, 162, 372, 50);
	HealthIcon = UCanvas::MakeIcon(HUDTexture, 78, 262, 28, 28);

}

void AProjectHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
	DrawHP();
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

void AProjectHUD::DrawHP()
{
	APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetOwningPawn());
	if (MyCharacter) {
		Canvas->SetDrawColor(FColor::White);
		float ScaleUI = Canvas->ClipY / 1080.0f;
		ScaleUI *= 2.0f;
		const float HealthPosX = (Canvas->ClipX - HealthBarBg.UL * ScaleUI) / 2;
		const float HealthPosY = Canvas->ClipY - (20.0f + HealthBarBg.VL) * ScaleUI;
		Canvas->DrawIcon(HealthBarBg, HealthPosX, HealthPosY, ScaleUI);

		const float HealthAmount = FMath::Min(1.0f, MyCharacter->GetCurrentHP() / MyCharacter->GetMaxHP());
		if (HealthAmount > 0.0f) {
			FCanvasTileItem TileItem(FVector2D(HealthPosX, HealthPosY), HealthBar.Texture->Resource,
				FVector2D(HealthBar.UL * HealthAmount * ScaleUI, HealthBar.VL * ScaleUI), FLinearColor::White);

			MakeUV(HealthBar, TileItem.UV0, TileItem.UV1, HealthBar.U, HealthBar.V, HealthBar.UL * HealthAmount, HealthBar.VL);
			TileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(TileItem);
		}
	}
}

void AProjectHUD::MakeUV(FCanvasIcon & Icon, FVector2D & UV0, FVector2D & UV1, uint16 U, uint16 V, uint16 UL, uint16 VL)
{
	if (Icon.Texture)
	{
		const float Width = Icon.Texture->GetSurfaceWidth();
		const float Height = Icon.Texture->GetSurfaceHeight();
		UV0 = FVector2D(U / Width, V / Height);
		UV1 = UV0 + FVector2D(UL / Width, VL / Height);
	}
}
