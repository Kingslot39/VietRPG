// Fill out your copyright notice in the Description page of Project Settings.


#include "EarthWall.h"

// Sets default values
AEarthWall::AEarthWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	EarthWallSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	EarthWallSprite->SetupAttachment(Root);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Root);

	// Collision setup
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionObjectType(ECC_WorldStatic);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);
	Collision->SetCanEverAffectNavigation(false);
	

}

void AEarthWall::EnableCollision()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AEarthWall::BeginPlay()
{
	Super::BeginPlay();
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Enable after short delay
	GetWorldTimerManager().SetTimer(Timer, this, &AEarthWall::EnableCollision, 0.05f, false);
	
}

// Called every frame
void AEarthWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

