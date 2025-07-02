// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWheelWidget.h"


void USkillWheelWidget::SelectSkill(EElementTag SkillTag)
{
	OnSkillSelected.Broadcast(SkillTag);
}

void USkillWheelWidget::UpdateSelectedSKill(EElementTag Chosen)
{
	SelectedSkillTag = Chosen;
}
