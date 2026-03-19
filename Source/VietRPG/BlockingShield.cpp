// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockingShield.h"
#include "MainCharacter.h"

// Sets default values
ABlockingShield::ABlockingShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
    

}



void ABlockingShield::DestroyShield()
{
	Destroy();
}



// Called when the game starts or when spawned
void ABlockingShield::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ShieldTimer, this, &ABlockingShield::DestroyShield, 0.7f, false);
	
}

// Called every frame
void ABlockingShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

