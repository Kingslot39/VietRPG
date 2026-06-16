// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_EnterPhase2.generated.h"

/**
 * Returns true when the boss has entered phase 2 (HP <= 50%).
 * Attach to a Sequence/Selector branch to gate phase-2-only skills.
 */
UCLASS()
class VIETRPG_API UBTD_EnterPhase2 : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_EnterPhase2();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};