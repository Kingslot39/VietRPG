// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWheelWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSelected, EWeaponType, SelectedSkill);
UCLASS()


class VIETRPG_API UWeaponWheelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponSelected OnWeaponSelected;

	UFUNCTION(BlueprintCallable)
	void SelectWeapon(EWeaponType WeaponType);
	
};
