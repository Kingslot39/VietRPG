// Fill out your copyright notice in the Description page of Project Settings.

#include "BTD_EnterPhase2.h"
#include "Boss1.h"
#include "ElderAIController.h"

UBTD_EnterPhase2::UBTD_EnterPhase2()
{
	NodeName = TEXT("Is Phase 2");
}

bool UBTD_EnterPhase2::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AElderAIController* AIController = Cast<AElderAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return false;

	ABoss1* Boss = Cast<ABoss1>(AIController->GetPawn());
	if (!Boss) return false;

	return Boss->bIsPhase2;
}