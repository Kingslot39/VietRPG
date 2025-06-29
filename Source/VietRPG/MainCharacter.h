// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
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
	virtual void Landed(const FHitResult& Hit) override;

	void UpdateAnimation();
	
private:
	void Tick(float DeltaSeconds) override;
    void BeginPlay() override;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);

};
