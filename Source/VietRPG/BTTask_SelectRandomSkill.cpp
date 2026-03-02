// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectRandomSkill.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SelectRandomSkill::UBTTask_SelectRandomSkill()
{
	NodeName = TEXT("Select Random Skill");

	SkillKey.AddEnumFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SelectRandomSkill, SkillKey),
		StaticEnum<EEnemySkill>()
	);
}

EEnemySkill UBTTask_SelectRandomSkill::ChooseWeighted(const TArray<FSkillWeight>& In) const
{
	double total = 0.0;
	for (const auto& e : In)
	{
		if (!bIgnoreZeroOrNegative || e.Weight > 0.f)
		{
			total += FMath::Max(0.0, static_cast<double>(e.Weight));
		}
	}
	if (total <= 0.0) return EEnemySkill::None;

	const double roll = FMath::FRand() * total;
	double acc = 0.0;

	for (const auto& e : In)
	{
		const double w = FMath::Max(0.0, static_cast<double>(e.Weight));
		if (bIgnoreZeroOrNegative && w <= 0.0) continue;

		acc += w;
		if (roll <= acc)
		{
			return e.Skill;
		}
	}
	return EEnemySkill::None;
}

EBTNodeResult::Type UBTTask_SelectRandomSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	const EEnemySkill chosen = ChooseWeighted(Weights);
	if (chosen == EEnemySkill::None) return EBTNodeResult::Failed;

	BB->SetValueAsEnum(SkillKey.SelectedKeyName, static_cast<uint8>(chosen));
	return EBTNodeResult::Succeeded;
}

