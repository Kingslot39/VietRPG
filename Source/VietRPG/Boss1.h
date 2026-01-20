// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Boss1.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API ABoss1 : public AEnemy
{
	GENERATED_BODY()
public:
	ABoss1();

private:
	void Tick(float DeltaSeconds) override;
	
	
	
	
};
