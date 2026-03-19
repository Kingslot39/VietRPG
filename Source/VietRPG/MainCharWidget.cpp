// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharWidget.h"
#include "MainCharacter.h"


void UMainCharWidget::UpdateHealthBar()
{
	
	if (!HealthBar || !Target)
	{
		// Either HealthBar or Target is null, can't update
		UE_LOG(LogTemp, Warning, TEXT("Cannot update health bar: %s is null"), 
			!HealthBar ? TEXT("HealthBar") : TEXT("Target"));
		return;
	}
    
	HealthBar->SetPercent((float)Target->CurrentHealth/Target->MaxHealth);
}

void UMainCharWidget::UpdateCircleProgress(const TArray<float>& EnergyProgress)
{
	for (int i = 0; i < Circles.Num(); i++)
	{
		if (EnergyProgress.IsValidIndex(i))
		{
			Circles[i]->SetPercent(EnergyProgress[i]);
		}
	}
}


void UMainCharWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Circles.Empty();
	Circles.Add(Circle1);
	Circles.Add(Circle2);
	Circles.Add(Circle3);
	Circles.Add(Circle4);
	Circles.Add(Circle5);
}

