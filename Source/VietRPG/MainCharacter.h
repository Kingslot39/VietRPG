// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "EnhancedInputSubsystems.h"
#include "ElementCombineComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "MainSkillWidget.h"
#include "SkillWheelWidget.h"
#include "Spell.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction3;
	
	

public:
	AMainCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;

	//Flipbook animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* JumpAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* LandingAnimation;

	virtual void Jump() override;
	FTimerHandle LandingDelayHandle;
	virtual void Landed(const FHitResult& Hit) override;

	void UpdateAnimation();

	//Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpell>SpellClass;

	UFUNCTION(BlueprintCallable)
	void ShootingSpellSkill();


	//Skill UI
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skill")
	TSubclassOf<UMainSkillWidget>MainSkillWidgetClass;
    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skill")
	TSubclassOf<USkillWheelWidget>SkillWheelWidgetClass;

	UPROPERTY()
	UMainSkillWidget* MainSkillWidget;
	UPROPERTY()
	USkillWheelWidget* SkillWheelWidget;

	UPROPERTY()
	EElementTag CurrentSkill = EElementTag::E_Air;
    bool bIsSkillWheelVisible = false;
	void ShowSkillWheel();
	void HideSkillWheel();
	void OnSkillSelected(EElementTag SelectedSkill);

    void SelectSkillLeft();
	void SelectSkillRight();
	void SelectSkillUp();
	
private:
	void Tick(float DeltaSeconds) override;
    void BeginPlay() override;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);

};
