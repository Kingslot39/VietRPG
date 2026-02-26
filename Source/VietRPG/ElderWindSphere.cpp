// Fill out your copyright notice in the Description page of Project Settings.


#include "ElderWindSphere.h"

// Sets default values
AElderWindSphere::AElderWindSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpellSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	RootComponent = SpellSprite;
	SpellSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpellSprite->SetCollisionProfileName("OverlapAllDynamic");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = LifeSpan;

}

void AElderWindSphere::SetDirection(float Direction)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = FVector(ProjectileMovement->InitialSpeed * Direction, 0.f, 0.f);
	}
}

// Called when the game starts or when spawned
void AElderWindSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElderWindSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

