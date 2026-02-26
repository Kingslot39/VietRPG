// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1.h"

ABoss1::ABoss1()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 1000;
	CurrentHealth = MaxHealth;
}

void ABoss1::UpdateAnimation()
{
	if (bIsShootingAir)
	{
		if (AirSphereShootingAnimation && GetSprite()->GetFlipbook() != AirSphereShootingAnimation)
		{
			GetSprite()->SetFlipbook(AirSphereShootingAnimation);
		}
		return;
	}
	else if (bIsMeditating)
	{
		if (MeditateAnimation && GetSprite()->GetFlipbook() != MeditateAnimation)
		{
			GetSprite()->SetFlipbook(MeditateAnimation);
		}
		return;
	}
	else if (bIsJumpingStone)
	{
		if (StoneRiftJumpAnimation && GetSprite()->GetFlipbook() != StoneRiftJumpAnimation)
		{
			GetSprite()->SetFlipbook(StoneRiftJumpAnimation);
		}
		return;
	}
	else
	{
		GetSprite()->SetFlipbook(IdleAnimation);
	}
}

void ABoss1::AirShootingSkill()
{
	float FacingDirection = FMath::Sign(Target->GetActorLocation().X - GetActorLocation().X);

	// Distance in front of the character
	const float ForwardOffset = 130.f;

	FVector SpawnLocation =
		GetActorLocation() +
		FVector(ForwardOffset * FacingDirection, 0.f, 0.f);

	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	AElderWindSphere* Projectile = GetWorld()->SpawnActor<AElderWindSphere>(
		ElderWindSphereClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (Projectile)
	{
		Projectile->SetDirection(FacingDirection);
	}
}

void ABoss1::ShootTwice()
{
	if (!IsValid(Target))
		return;
	bIsShootingAir = true;
	AirShootingSkill();

	GetWorld()->GetTimerManager().SetTimer(
		ShootTimerHandle,
		this,
		&ABoss1::AirShootingSkill,
		1.0f,
		false
	);
	GetWorld()->GetTimerManager().SetTimer(
		ResetAniTimeHandle,
		[this]()
		{
			bIsShootingAir = false;
		},
		1.0f,
		false
	);
    GetWorld()->GetTimerManager().SetTimer(SkillTransactionTimerHandle,this, &ABoss1::StoneRiftJump, 1.0f, false);
}

void ABoss1::SlamDown()
{
	FVector SlamVelocity = FVector(0.f, 0.f, -10000.f);
	LaunchCharacter(SlamVelocity, true, true);
	GetWorld()->GetTimerManager().SetTimer(StoneRiftJumpTimerHandle, this, &ABoss1::StoneShootTwice, 0.2f, false);
}

void ABoss1::StoneRiftJump()
{
	// Prevent other animations from overriding this
	bIsJumpingStone = true;
	
    FVector TargetLocation = Target->GetActorLocation();
	FVector Start = GetActorLocation();

	// Direction only in X (2D)
	float DirectionX = TargetLocation.X > Start.X ? 1.f : -1.f;

	// Horizontal distance
	float DistanceX = FMath::Abs(TargetLocation.X - Start.X);

	// Tunable values
	float JumpHorizontalSpeed = 600.f;
	float JumpVerticalSpeed = 900.f;

	FVector LaunchVelocity;
	LaunchVelocity.X = DirectionX * JumpHorizontalSpeed;
	LaunchVelocity.Y = 0.f;
	LaunchVelocity.Z = JumpVerticalSpeed;


	// Launch toward target
	LaunchCharacter(LaunchVelocity, true, true);

	// After 2 seconds → force slam down
	GetWorldTimerManager().SetTimer(
		SlamTimerHandle,
		this,
		&ABoss1::SlamDown,
		1.0f,
		false
	);
}

void ABoss1::StoneShootTwice()
{
	StoneRiftShoot();
	GetWorld()->GetTimerManager().SetTimer(StoneShootTwiceTimerHandle, this, &ABoss1::StoneRiftShoot, 0.5f, false);
	GetWorld()->GetTimerManager().SetTimer(
		ResetAniJumpTimerHandle,
		[this]()
		{
			bIsJumpingStone = false;
		},
		0.4,
		false
	);

	
}

void ABoss1::StoneRiftShoot()
{
	FVector StartLocation = GetActorLocation();

	// Direction toward target (2D: X only)
	FVector TargetDirection = (Target->GetActorLocation() - StartLocation);
	TargetDirection.Y = 0.f;
	TargetDirection.Z = 0.f;
	TargetDirection.Normalize();

	const float ForwardOffset = 130.f;

	FVector SpawnLocation = StartLocation + TargetDirection * ForwardOffset - FVector(0,0,50) ;

	FRotator SpawnRotation = TargetDirection.Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	AElderStoneRift* Projectile = GetWorld()->SpawnActor<AElderStoneRift>(
		ElderStoneRiftClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
	if (Projectile)
	{
		Projectile->SetMoveDirection(TargetDirection.X); // 2D-friendly
	}
}

void ABoss1::Meditate()
{
	bIsMeditating = true;
	CurrentSpawnCount = 0;

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ABoss1::SpawnTrap,
		SpawnInterval,
		true
	);
	
}
void ABoss1::SpawnTrap()
{
	if (CurrentSpawnCount >= SpawnCountMax)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	FVector SpawnLocation = Target->GetActorLocation()- FVector(0,0,60);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	AElderWaterSphere* WaterBomb = GetWorld()->SpawnActor<AElderWaterSphere>(
		WaterSphereClass,
		SpawnLocation,
		SpawnRotation
	);
	CurrentSpawnCount ++;
}

void ABoss1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateAnimation();
	
}

void ABoss1::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ShootTwice();
	
}
