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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Dashing;
	
	

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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* SkillAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* DashAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* WindShootAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* WallRisingAnimation;

	//Dashing
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsDashing = false;
    UFUNCTION(BlueprintCallable)
	bool SetIsDashing(bool NewDashing);
	
	//Jumping / Landing
	void CheckIsJumping();
	void JumpingIsNot();
	void StopDashing();
	FTimerHandle StopDashingTimer;
	FTimerHandle JumpTimer;
	bool bIsJumping = false;
	
	FTimerHandle LandingDelayHandle;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector TeleportFoward();

	
    UFUNCTION(BlueprintCallable)
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
	  // Projectile Skill
	UFUNCTION(BlueprintCallable)
	void ShootingSpellSkill();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTimerHandle ShootingAirTimerHandle;
    bool bIsShootingAir = false; 
	  //EarthWall
	UFUNCTION(BlueprintCallable)
	void EarthWallSkill();
    bool bWallRising = false;
	
	UFUNCTION(BlueprintCallable)
	void WindShieldSkill();
	UFUNCTION(BlueprintCallable)
	void WaterSwordSlice();

	//Unable to move
	UFUNCTION(BlueprintCallable)
	void EnableMovement();
	FTimerHandle DisableMovementTimerHandle;

	


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
