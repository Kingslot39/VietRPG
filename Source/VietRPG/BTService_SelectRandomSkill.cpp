// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SelectRandomSkill.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SelectRandomSkill::UBTService_SelectRandomSkill()
{
	bNotifyBecomeRelevant = true;
}

void UBTService_SelectRandomSkill::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const int32 RandomSkill = FMath::RandRange(0, 2); // 3 skills: 0,1,2
	OwnerComp.GetBlackboardComponent()->SetValueAsInt("SelectedSkill", RandomSkill);
}