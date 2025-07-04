// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSkillWidget.h"

void UMainSkillWidget::UpdateSkillIcon(EElementTag NewSKillTag)
{
    CurrentSkillTag = NewSKillTag;
	if (IconMap.Contains(NewSKillTag) && SkillIcon)
		SkillIcon->SetBrushFromTexture(IconMap[NewSKillTag]);
}

EElementTag UMainSkillWidget::GetCurrentSkillTag()
{
	return  CurrentSkillTag;
}

