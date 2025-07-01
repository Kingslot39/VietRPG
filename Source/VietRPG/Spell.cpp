// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"

#include "Enemy.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpellSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	RootComponent = SpellSprite;
	SpellSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpellSprite->SetCollisionProfileName("OverlapAllDynamic");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = LifeSpan;

}

void ASpell::SetDirection(float Direction)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = FVector(ProjectileMovement->InitialSpeed * Direction, 0.f, 0.f);
	}

	// Flip sprite if going left
	if (Direction < 0)
	{
		SpellSprite->SetRelativeScale3D(FVector(-1.f, 1.f, 1.f));
	}
	else
	{
		SpellSprite->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}
}




// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

