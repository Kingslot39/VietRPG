// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SelectRandomSkill.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UBTService_SelectRandomSkill : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_SelectRandomSkill();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
	int32 NumberOfSkills = 3;
	
};
