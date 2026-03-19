 // Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1.h"

#include "SelectionSet.h"

 ABoss1::ABoss1()
{
 
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 2000;
	CurrentHealth = MaxHealth;
}

 void ABoss1::DealDamage(float Damage)
 {
	CurrentHealth -= Damage;
	if (ElderBossWidget)
	{
		ElderBossWidget->UpdateValue();
	}
	
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
	else if (bIsCastingFirePillar)
	{
		if (FirePillarAnimation && GetSprite()->GetFlipbook() != FirePillarAnimation)
		{
			GetSprite()->SetFlipbook(FirePillarAnimation);
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
if(bIsShootingAir){
	FaceTarget();
    bCanMeditate = false;
    bCanFire = false;
	float FacingDirection = FMath::Sign(Target->GetActorLocation().X - GetActorLocation().X);

	// Distance in front of the character
	const float ForwardOffset = 130.f;

	FVector SpawnLocation =
		GetActorLocation() +
		FVector(ForwardOffset * FacingDirection, 0.f, 0.f) + FVector(0, 3, 0.f);

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
		1.3f,
		false
	);
    GetWorld()->GetTimerManager().SetTimer(SkillTransactionTimerHandle,this, &ABoss1::WaitForJumpAni, 1.0f, false);
 	
}

void ABoss1::SlamDown()
{
	FVector SlamVelocity = FVector(0.f, 0.f, -10000.f);
	LaunchCharacter(SlamVelocity, true, true);
	GetWorld()->GetTimerManager().SetTimer(StoneRiftJumpTimerHandle, this, &ABoss1::StoneRiftShoot, 0.2f, false);
}

void ABoss1::StoneRiftJump()
{
	// Prevent other animations from overriding this
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

void ABoss1::StoneRiftShoot()
{
	FVector StartLocation = GetActorLocation();


	FVector SpawnLocation = StartLocation  - FVector(0,0,50) + FVector(0,3,0) ;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	AElderStoneRift* Projectile = GetWorld()->SpawnActor<AElderStoneRift>(
		ElderStoneRiftClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
 	GetWorld()->GetTimerManager().SetTimer(ResetSkillAirStrikeTimer, this, &ABoss1::ResetSkillFromAirStrike, 1.3f, false);
}

 void ABoss1::WaitForJumpAni()
 {
 	bIsJumpingStone = true;
 		// After 1.5 seconds, shoot the stone rift
 	GetWorld()->GetTimerManager().SetTimer(ResetAniJumpTimerHandle, this, &ABoss1::StoneRiftJump, 0.3f, false);
 }

 void ABoss1::Meditate()
{
	if (bCanMeditate)
	{
		
		bCanAirStrike = false;
		bCanFire = false;
		bIsMeditating = true;
		bIsJumpingStone = false;
		CurrentSpawnCount = 0;
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&ABoss1::SpawnTrap,
			1.5f,
			true
		);
	}
	
}
void ABoss1::SpawnTrap()
{
	if (CurrentSpawnCount >= SpawnCountMax)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(ResetSkillMeditateTimer, this, &ABoss1::ResetSkillFromMeditate, 2.0f, false);
		return;
	}

	FVector SpawnLocation = Target->GetActorLocation()- FVector(0,0,20) + FVector(0,3,0);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	AElderWaterSphere* WaterBomb = GetWorld()->SpawnActor<AElderWaterSphere>(
		WaterSphereClass,
		SpawnLocation,
		SpawnRotation
	);
	CurrentSpawnCount ++;
}


void ABoss1::FireStep()
{
	if (bCanFire)
	{
		FaceTarget();
		bCanMeditate = false;
		bCanAirStrike = false;
		bIsCastingFirePillar= true;
		GetWorldTimerManager().SetTimer(FirePillarTimer, this, &ABoss1::CastFirePillar, 0.7f, false);
	}
}

void ABoss1::CastFirePillar()
{
	

 	FVector StartLocation = GetActorLocation();

 	// 2D direction (-1 = left, 1 = right)
 	float Dir = (GetActorScale3D().X > 0) ? 1.f : -1.f;

 	// Spawn in front of character
 	FVector FireSpawnLocation = StartLocation - FVector(Dir * 760.f, 0.f, 90.f);

 	// Rotate correctly
 	FRotator FireSpawnRotation = (Dir > 0)
		 ? FRotator(0.f, 0.f, 0.f)     // facing right
		 : FRotator(0.f, 180.f, 0.f);  // facing left

 	FActorSpawnParameters SpawnParams;
 	SpawnParams.Owner = this;
 	SpawnParams.Instigator = this;

 	AFireColumn* FireColumn = GetWorld()->SpawnActor<AFireColumn>(
		 FireColumnClass,
		 FireSpawnLocation,
		 FireSpawnRotation,
		 SpawnParams
	 );
	GetWorldTimerManager().SetTimer(
		FireColumnTimer,
		this,
		&ABoss1::SpawnFireColumn,
		0.7f,
		false);
}

void ABoss1::SpawnFireColumn()
{
 	FVector StartLocation = GetActorLocation() + FVector(0, 0, 40);

 	// Get facing direction from scale (same as your fire skill)
 	float Dir = (Target->GetActorLocation().X > GetActorLocation().X) ? 1.f : -1.f;

 	float Spacing = 300.f;

 	for (int i = 1; i <= 6; i++)
 	{
 		FVector SpawnLocation = StartLocation + FVector(Dir * Spacing * i, 0.f, 0.f);

 		GetWorld()->SpawnActor<AFireBloomPillar>(
			 FireBloomPillarClass,
			 SpawnLocation,
			 FRotator::ZeroRotator
		 );
 	}
	GetWorldTimerManager().SetTimer(ResetSkillFireTimer, this, &ABoss1::ResetSkillFromFire, 0.8f, false);
}


 void ABoss1::FaceTarget()
 {
	if (!Target) return;

	FVector MyLocation = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	float RotateDirection = TargetLocation.X - MyLocation.X;

	if (RotateDirection < 0)
	{
		SetActorScale3D(FVector(1.5, 1.5, 1.5));   // Face Right
	}
	else
	{
		SetActorScale3D(FVector(-1.5, 1.5, 1.5));  // Face Left
	}
 }

void ABoss1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateAnimation();
	
}

void ABoss1::ResetSkillFromAirStrike()
{
	bCanAirStrike = false;
 	bIsJumpingStone = false;
	bCanFire = true;
	bCanMeditate = true;
}

void ABoss1::ResetSkillFromFire()
{
	bIsCastingFirePillar = false;
	bCanAirStrike = true;
	bCanMeditate = true;
}
void ABoss1::ResetSkillFromMeditate()
{
	bIsMeditating = false;
	bCanAirStrike = true;
	bCanFire = true;
}


void ABoss1::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (ElderBossWidget)
	{
		ElderBossWidget = CreateWidget<UElderBossWidget>(GetGameInstance(),ElderHealthBar);
		if (ElderBossWidget)
		{
			ElderBossWidget->AddToViewport();
			ElderBossWidget->Target = this;
			ElderBossWidget->UpdateValue();
		}
	}
	
	
	
}
