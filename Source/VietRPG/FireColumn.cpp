// Fill out your copyright notice in the Description page of Project Settings.


#include "FireColumn.h"

// Sets default values
AFireColumn::AFireColumn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFireColumn::DestroyActor()
{
	Destroy();
}

// Called when the game starts or when spawned
void AFireColumn::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AFireColumn::DestroyActor, 2.0f, false);
}

// Called every frame
void AFireColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

