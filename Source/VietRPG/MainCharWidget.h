// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MainCharWidget.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UMainCharWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY()
	class AMainCharacter* Target;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Circle1;

	UPROPERTY(meta = (BindWidget))
	 UProgressBar* Circle2;

	UPROPERTY(meta = (BindWidget))
	 UProgressBar* Circle3;

	UPROPERTY(meta = (BindWidget))
	 UProgressBar* Circle4;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Circle5;

	TArray<UProgressBar*> Circles;

	int CurrentUnits = 0;
	const int UnitsPerCircle = 2;

	
	void UpdateHealthBar();
	void UpdateCircleProgress(const TArray<float>& EnergyProgress);

	void NativeConstruct() override;
	
	
	
	
	
};
