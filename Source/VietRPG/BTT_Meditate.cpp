// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Meditate.h"

#include "ElderAIController.h"

UBTT_Meditate::UBTT_Meditate()
{
	NodeName = "Meditate";
}

EBTNodeResult::Type UBTT_Meditate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BTComp = &OwnerComp;
	if (!BTComp)
	{
		return EBTNodeResult::Failed;
	}
	AElderAIController* AIController = Cast<AElderAIController>(BTComp->GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	AIController->BossMeditate();
	return EBTNodeResult::Succeeded;
}
