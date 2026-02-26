// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_AirSphere.h"

#include "ElderAIController.h"

UBTT_AirSphere::UBTT_AirSphere()
{
	NodeName = "Air Sphere";
	
}

EBTNodeResult::Type UBTT_AirSphere::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	AIController->Shoot();
	return EBTNodeResult::Succeeded;
}
