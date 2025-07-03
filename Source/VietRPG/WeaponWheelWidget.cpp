// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWheelWidget.h"

void UWeaponWheelWidget::SelectWeapon(EWeaponType WeaponType)
{
	OnWeaponSelected.Broadcast(WeaponType);
}
