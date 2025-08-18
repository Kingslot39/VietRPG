// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//ElementCombineComponent = CreateDefaultSubobject<UElementCombineComponent>(TEXT("Element Component"));

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

void AEnemy::GetDamage(float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
}

void AEnemy::PosionSmokeStart(float Damage, float Duration)
{
	DotDamageAmount = Damage;
	DotDuration = Duration;
	DotTimeElapsed = 0.f;

	// Start timer to call DealDotDamage every 1 second, looped
	GetWorldTimerManager().SetTimer(DotDamageTimerHandle, this, &AEnemy::PosionSmokeApply, 1.0f, true);
}

void AEnemy::PosionSmokeApply()
{
	// Apply damage
	CurrentHealth -= DotDamageAmount;

	// You can add a check here to prevent Health < 0
	if (CurrentHealth <= 0.f)
	{
		CurrentHealth = 0.f;
		// Handle death logic here
		GetWorldTimerManager().ClearTimer(DotDamageTimerHandle);
		return;
	}

	// Increase elapsed time
	DotTimeElapsed += 1.f;

	// Check if duration expired
	if (DotTimeElapsed >= DotDuration)
	{
		GetWorldTimerManager().ClearTimer(DotDamageTimerHandle);
	}
}

void AEnemy::Freeze(float Duration)
{
	bIsFreeze = true;
	GetCharacterMovement()->DisableMovement();
	SpriteComponent = this->GetSprite();
	SpriteComponent = Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	if (SpriteComponent)
	{
		SpriteComponent->Stop();// Freeze current animation frame
		SpriteComponent->SetSpriteColor(FColor::Blue);
	}

	// Set timer to unfreeze
	GetWorldTimerManager().SetTimer(FreezeTimeHandle, this, &AEnemy::UnFreeze, Duration, false);
}

void AEnemy::UnFreeze()
{
	bIsFreeze = false;

	// Re-enable movement
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	SpriteComponent->Play();
	

	// Resume sprite animation
	if (SpriteComponent && SpriteComponent->GetFlipbook())
	{
		SpriteComponent->Play();
	}
}

