// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterSwordSlice.h"

// Sets default values
AWaterSwordSlice::AWaterSwordSlice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	SpellSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	RootComponent = SpellSprite;
	SpellSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpellSprite->SetCollisionProfileName("OverlapAllDynamic");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1300.f;
	ProjectileMovement->MaxSpeed = 1300.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = LifeSpan;

}


void AWaterSwordSlice::SetDirection(AActor* Target)
{
	HomingTarget = Target;

	if (HomingTarget)
	{
		ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
	}
}

// Called when the game starts or when spawned
void AWaterSwordSlice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterSwordSlice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

