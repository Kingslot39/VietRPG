// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FireSlam.h"

#include "ElderAIController.h"

UBTT_FireSlam::UBTT_FireSlam()
{
	NodeName = "Fire Slam";
}

EBTNodeResult::Type UBTT_FireSlam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	AIController->FireSlam();
	return EBTNodeResult::Succeeded;
}
