// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API AEnemy : public APaperCharacter
{
	GENERATED_BODY()
public:
	AEnemy();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbook* WalkAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 100.f;

	// Movement direction
	int32 Direction = -1; // -1 = left, 1 = right

	void Move(float DeltaTime);

	// Set animation depending on state
	void UpdateAnimation();
};
