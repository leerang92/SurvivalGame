// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "UsableActor.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
namespace EItemType
{
	enum Type
	{
		None,
		Weapon,
		Helmet,
	};
}

USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	int Amount;

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	TEnumAsByte<enum EItemType::Type> ItemType;

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	TSubclassOf<class AUsableActor> ItemClass;

public:

	FItemInformation() 
		: Name(TEXT("No Name"))
		, Amount(0)
		, Image(nullptr)
		, ItemType(EItemType::None)
		, ItemClass(nullptr)
	{}
};


