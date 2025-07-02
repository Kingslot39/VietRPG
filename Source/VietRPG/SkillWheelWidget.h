// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ElementCombineComponent.h"
#include "SkillWheelWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillSelected, EElementTag, SelectedSkill);
UCLASS()
class VIETRPG_API USkillWheelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Skill Wheel")
	FOnSkillSelected OnSkillSelected;

	UFUNCTION(BlueprintCallable, Category = "Skill Wheel")
	void SelectSkill(EElementTag SkillTag);
	


};
