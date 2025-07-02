// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElementCombineComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API UMainSkillWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Skill Widget")
	void UpdateSkillIcon (EElementTag NewSKillTag);

protected:
	UPROPERTY(meta= (BindWidget))
	UImage* SkillIcon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skill Widget")
	TMap<EElementTag, UTexture2D*> IconMap;
	
};
