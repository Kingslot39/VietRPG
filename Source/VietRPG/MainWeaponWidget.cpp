// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWeaponWidget.h"

void UMainWeaponWidget::UpdateWeaponIcon(EWeaponType NewWeaponType)
{
	if (IconMaps.Contains(NewWeaponType) && SkillIcon)
		SkillIcon->SetBrushFromTexture(IconMaps[NewWeaponType]);
}
