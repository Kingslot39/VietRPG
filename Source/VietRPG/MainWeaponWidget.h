// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UMainWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon Widget")
	void UpdateWeaponIcon(EWeaponType NewWeaponType);

	UPROPERTY(meta= (BindWidget))
	UImage* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Widget")
	TMap<EWeaponType, UTexture2D*> IconMaps;
	
	
	
};
