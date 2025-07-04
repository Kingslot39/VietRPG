// Fill out your copyright notice in the Description page of Project Settings.


#include "EarthWall.h"

// Sets default values
AEarthWall::AEarthWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EarthWallSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EarthWallSprite"));
	RootComponent = EarthWallSprite;
	EarthWallSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EarthWallSprite->SetCollisionProfileName("BlockAllDynamic");

}

// Called when the game starts or when spawned
void AEarthWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEarthWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

