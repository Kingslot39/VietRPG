// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	CurrentHealth = MaxHealth = 100.f;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemy::Move(float DeltaTime)
{
	AddMovementInput(FVector(Direction,0,0), MoveSpeed * DeltaTime);
}

void AEnemy::UpdateAnimation()
{
	if(GetVelocity().SizeSquared()>0)
	{
		if (WalkAnimation && GetSprite()->GetFlipbook() != WalkAnimation)
		{
			GetSprite()->SetFlipbook(WalkAnimation);
		}
	}
	else
	{
		if(IdleAnimation && GetSprite()->GetFlipbook() != IdleAnimation)
		{
			GetSprite()->SetFlipbook(IdleAnimation);
		}
	}
}
