// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneRiftBullet.h"

#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AStoneRiftBullet::AStoneRiftBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	RootComponent = SpellSprite;

	SpellSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpellSprite->SetCollisionProfileName("OverlapAllDynamic");

	// IMPORTANT: no absolute scale
	SpellSprite->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	Speed = 1200.f;
	MoveDirection = 1.f;

	InitialLifeSpan = LifeSpan;

}

void AStoneRiftBullet::SetMoveDirection(float Direction)
{
	MoveDirection = FMath::Sign(Direction);
}

// Called when the game starts or when spawned
void AStoneRiftBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoneRiftBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location.X += MoveDirection * Speed * DeltaTime;

	SetActorLocation(Location, true);

}

