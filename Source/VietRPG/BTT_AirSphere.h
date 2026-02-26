// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_AirSphere.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UBTT_AirSphere : public UBTTaskNode
{
	GENERATED_BODY()
	UBTT_AirSphere();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
