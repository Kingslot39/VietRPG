// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWheelWidget.h"
#include "MainSkillWidget.h"


void USkillWheelWidget::SelectSkill(EElementTag SkillTag)
{
	OnSkillSelected.Broadcast(SkillTag);
}



