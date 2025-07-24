// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EarthWall.h"
#include "PaperCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "ElementCombineComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "MainSkillWidget.h"
#include "MainWeaponWidget.h"
#include "SkillWheelWidget.h"
#include "Spell.h"
#include "WaterSwordSlice.h"
#include "WeaponWheelWidget.h"
#include "WindShield.h"
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
    //Skill Select
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillWheelSelectAction4;

	//Weapon Select
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponWheelSelectActionLeft;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponWheelSelectActionRight;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponWheelSelectActionUp;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponWheelSelectDown;
	
	

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EElementTag CurrentSkill;

	//Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpell>SpellClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEarthWall>EarthWallClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWindShield>WindShieldClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWaterSwordSlice>WaterSwordSliceClass;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void ActivateSkill();
	
	//Skill List
	UFUNCTION(BlueprintCallable)
	void ShootingSpellSkill();
	UFUNCTION(BlueprintCallable)
	void EarthWallSkill();
	UFUNCTION(BlueprintCallable)
	void WindShieldSkill();
	UFUNCTION(BlueprintCallable)
	void WaterSwordSlice();


	//Find Enemy
	AActor* NearestEnemy(FVector2D Origin);


	//Skill UI
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skill")
	TSubclassOf<UMainSkillWidget>MainSkillWidgetClass;
    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skill")
	TSubclassOf<USkillWheelWidget>SkillWheelWidgetClass;
	UPROPERTY()
	UMainSkillWidget* MainSkillWidget;
	UPROPERTY()
	USkillWheelWidget* SkillWheelWidget;

	//Weapon UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UMainWeaponWidget>MainWeaponWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UWeaponWheelWidget>WeaponWheelWidgetClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMainWeaponWidget* MainWeaponWidget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWeaponWheelWidget* WeaponWheelWidget;

	
	UPROPERTY()
    bool bIsSkillWheelVisible = false;
	void ShowSkillWheel();
	void HideSkillWheel();
	void OnSkillSelected(EElementTag SelectedSkill);
	void OnWeaponSelected(EWeaponType SelectedWeapon);
	UPROPERTY()
	EWeaponType CurrentWeapon;
    //Select Skill
    void SelectSkillLeft();
	void SelectSkillRight();
	void SelectSkillUp();
	void SelectSkillDown();
    //Select Weapon
	void SelectWeaponLeft();
	void SelectWeaponRight();
	void SelectWeaponUp();
	void SelectWeaponDown();
private:
	void Tick(float DeltaSeconds) override;
    void BeginPlay() override;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);

};
