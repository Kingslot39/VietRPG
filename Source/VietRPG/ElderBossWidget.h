// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ElderBossWidget.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UElderBossWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABoss1* Target;
	void UpdateValue();
	
};
