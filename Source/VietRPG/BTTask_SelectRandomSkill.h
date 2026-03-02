// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Boss1.h"
#include "BTTask_SelectRandomSkill.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSkillWeight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemySkill Skill = EEnemySkill::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0"))
	float Weight = 1.f;
};

UCLASS()
class VIETRPG_API UBTTask_SelectRandomSkill : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTask_SelectRandomSkill();

protected:
	/** Blackboard enum key: SelectedSkill */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector SkillKey;

	/** Skills and their weights (Fireball=3, Dash=1, etc.) */
	UPROPERTY(EditAnywhere, Category="Randomization")
	TArray<FSkillWeight> Weights;

	/** Optional: skip zero or negative weights */
	UPROPERTY(EditAnywhere, Category="Randomization")
	bool bIgnoreZeroOrNegative = true;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	EEnemySkill ChooseWeighted(const TArray<FSkillWeight>& In) const;
};

	

