// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBloomPillar.h"

// Sets default values
AFireBloomPillar::AFireBloomPillar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFireBloomPillar::DestroyPillar()
{
	Destroy();
}

// Called when the game starts or when spawned
void AFireBloomPillar::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyWaitTime, this, &AFireBloomPillar::DestroyPillar, 0.9f,false);
	
}

// Called every frame
void AFireBloomPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

