// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1.h"

ABoss1::ABoss1()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 1000;
	CurrentHealth = MaxHealth;
}

void ABoss1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
