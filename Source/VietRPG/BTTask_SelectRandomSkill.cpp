// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectRandomSkill.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SelectRandomSkill::UBTTask_SelectRandomSkill()
{
	NodeName = "Select Random Skill";
    
	UEnum* EnumAsset = LoadObject<UEnum>(nullptr, TEXT("/Game/Enemy/Boss/ElderSkillEnum.ElderSkillEnum"));

	if (EnumAsset)
	{
		SkillKey.AddEnumFilter(
			this,
			GET_MEMBER_NAME_CHECKED(UBTTask_SelectRandomSkill, SkillKey),
			EnumAsset
		);
	}
	
}

EEnemySkill UBTTask_SelectRandomSkill::ChooseWeighted(const TArray<FSkillWeight>& In) const
{
	double TotalWeight = 0.0;

	for (const FSkillWeight& Entry : In)
	{
		if (bIgnoreZeroOrNegative && Entry.Weight <= 0.f)
			continue;

		TotalWeight += FMath::Max(0.f, Entry.Weight);
	}

	if (TotalWeight <= 0.0)
		return EEnemySkill::None;

	const double Roll = FMath::FRandRange(0.0, TotalWeight);
	double Acc = 0.0;

	for (const FSkillWeight& Entry : In)
	{
		if (bIgnoreZeroOrNegative && Entry.Weight <= 0.f)
			continue;

		Acc += Entry.Weight;

		if (Roll < Acc)
		{
			return Entry.Skill;
		}
	}

	// fallback
	return In.Last().Skill;
}

EBTNodeResult::Type UBTTask_SelectRandomSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB)
		return EBTNodeResult::Failed;

	// Choose a random skill
	const EEnemySkill chosen = ChooseWeighted(Weights);

	if (chosen == EEnemySkill::None)
		return EBTNodeResult::Failed;

	// SET BLACKBOARD VALUE HERE
	const uint8 SkillValue = static_cast<uint8>(chosen);
	BB->SetValueAsEnum(SkillKey.SelectedKeyName, SkillValue);

	return EBTNodeResult::Succeeded;

}

