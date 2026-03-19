// Fill out your copyright notice in the Description page of Project Settings.


#include "ElderWaterSphere.h"

// Sets default values
AElderWaterSphere::AElderWaterSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AElderWaterSphere::DestroySphere()
{
	Destroy();
}

// Called when the game starts or when spawned
void AElderWaterSphere::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(RemainTimerHandle, this, &AElderWaterSphere::DestroySphere, 1.5f, false);
	
}

// Called every frame
void AElderWaterSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

