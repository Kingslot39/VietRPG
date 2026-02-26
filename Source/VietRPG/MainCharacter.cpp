// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"


AMainCharacter::AMainCharacter()
{
	
}

void AMainCharacter::TakeDamage(float DamageAmount)
{
	if (bShieldActive)
	{
		return;
	}
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		// Handle death (e.g., play animation, disable input, etc.)
		CurrentHealth = 0;
	}
}

void AMainCharacter::Heal(float HealAmount)
{
	return;
}

bool AMainCharacter::SetIsDashing(bool NewDashing)
{ 
	bIsDashing = NewDashing;
	return bIsDashing;
}

void AMainCharacter::CheckIsJumping()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();

	if (!Capsule) return;

	const float CapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	const float GroundCheckDistance = 5.0f; // small tolerance

	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, CapsuleHalfHeight + GroundCheckDistance);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bOnGround = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	// Jumping = NOT touching ground
	bIsJumping = !bOnGround;

}

void AMainCharacter::JumpingIsNot()
{
	bIsJumping = false;
}

void AMainCharacter::StopDashing()
{
	bIsDashing = false;
	if (GetCharacterMovement()->IsFalling())
	{
		if (JumpAnimation)
			GetSprite()->SetFlipbook(JumpAnimation);
	}
}



FVector AMainCharacter::TeleportFoward()
{
	float TeleportDistance = 500.f;
    
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation;

	// Determine if we're facing right or left (using sprite flip or scale)
	bool bFacingRight = GetSprite()->GetRelativeScale3D().X > 0;

	if (bFacingRight)
	{
		// Move to the right
		NewLocation.X += TeleportDistance;
	}
	else
	{
		// Move to the left
		NewLocation.X -= TeleportDistance;
	}
    return NewLocation;
	// Instantly teleport to new location
	//SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}



void AMainCharacter::UpdateAnimation()
{
	if (GetWorldTimerManager().IsTimerActive(LandingDelayHandle))
	{
		return;
	}

	EWeaponType SelectedWeapon = MainWeaponWidget->GetCurrentWeaponType();
	float Speed = GetVelocity().Size();

	bool bInAir = GetCharacterMovement()->IsFalling();

	// --------------------------
	// 1. DASH (highest priority)
	// --------------------------
	if (bIsDashing && DashAnimation)
	{
		if (GetSprite()->GetFlipbook() != DashAnimation)
		{
			GetSprite()->SetFlipbook(DashAnimation);
			GetWorldTimerManager().SetTimer(
				StopDashingTimer, this, &AMainCharacter::StopDashing,
				0.08f, false
			);
		}
		return;
	}
	// ----------------------
	// 3. JUMP / FALL
	// ----------------------
	if (bInAir)
	{
		if (JumpAnimation && GetSprite()->GetFlipbook() != JumpAnimation)
		{
			GetSprite()->SetFlipbook(JumpAnimation);
		}
		return;
	}

	// ----------------------
	// 4. MOVING
	// ----------------------
	if (Speed > 1.0f)
	{
		if (SelectedWeapon == EWeaponType::E_Staff)
		{
			if (WalkAnimation && GetSprite()->GetFlipbook() != WalkAnimation)
			{
				GetSprite()->SetFlipbook(WalkAnimation);
			}
			return;
		}
		else if (SelectedWeapon == EWeaponType::E_Sword)
		{
			if (SwordWalkAnimation && GetSprite()->GetFlipbook() != SwordWalkAnimation)
			{
				GetSprite()->SetFlipbook(SwordWalkAnimation);
			}
			return;
		}
	}

	// ----------------------
	// 5. IDLE
	// ----------------------
	ChooseSkillAnimation(SelectedWeapon);
}

void AMainCharacter::ChooseSkillAnimation(EWeaponType SelectedWeapon)
{
	if ( SelectedWeapon == EWeaponType::E_Staff)
	{
		
		if (bIsShootingAir)
		{
			
			if (bIsJumping)
			{
				if (AirWindShootAnimation && GetSprite()->GetFlipbook() != AirWindShootAnimation)
				{
					GetSprite()->SetFlipbook(AirWindShootAnimation);
				}
			}
			else
			{
				if (WindShootAnimation && GetSprite()->GetFlipbook() != WindShootAnimation)
				{
					GetSprite()->SetFlipbook(WindShootAnimation);
				}
			}
		}
		else if(bWallRising)
		{
			if (WallRisingAnimation && GetSprite()->GetFlipbook() != WallRisingAnimation)
			{
				GetSprite()->SetFlipbook(WallRisingAnimation);
			}
		}
		else
		{
			if (IdleAnimation && GetSprite()->GetFlipbook() != IdleAnimation)
			{
				GetSprite()->SetFlipbook(IdleAnimation);
			}
		}
	}
	if (SelectedWeapon == EWeaponType::E_Sword)
	{
		if (bSwordRising)
		{
			if (StoneSwordAnimation && GetSprite()->GetFlipbook() != StoneSwordAnimation)
			{
				GetSprite()->SetFlipbook(StoneSwordAnimation);
			}
		}
	
		
		else
		{
			if (GetVelocity().Size() > 1.0f)
			{
				if (SwordWalkAnimation && GetSprite()->GetFlipbook() != SwordWalkAnimation)
				{
					GetSprite()->SetFlipbook(SwordWalkAnimation);
				}
			}
			else
			{
				if (SwordIdleAnimation && GetSprite()->GetFlipbook() != SwordIdleAnimation)
				{
					GetSprite()->SetFlipbook(SwordIdleAnimation);
				}
			}
		}
		
	}
}


void AMainCharacter::ActivateSkill()
{
	if(MainSkillWidget)
	{
	    if (SkillAnimation){
	      GetSprite()->SetFlipbook(SkillAnimation);
	    	GetSprite()->SetRelativeScale3D(FVector(1, 1, 1));
	    }
		EElementTag SelectedSkill = MainSkillWidget->GetCurrentSkillTag();
		EWeaponType SelectedWeapon = MainWeaponWidget->GetCurrentWeaponType();
		// Staff + air
		if(SelectedSkill == EElementTag::E_Air && SelectedWeapon == EWeaponType::E_Staff)
		{
			//ShootingSpellSkill();
		}
		//Staff + earth
		else if(SelectedSkill == EElementTag::E_Earth && SelectedWeapon == EWeaponType::E_Staff)
		{
			EarthWallSkill();
			bWallRising = true;
			GetWorldTimerManager().SetTimer(ShootingAirTimerHandle, this, &AMainCharacter::EarthWallSkill, 1.0f, false);
			GetSprite()->SetFlipbook(WallRisingAnimation);
			GetCharacterMovement()->DisableMovement();
			GetWorldTimerManager().SetTimer(DisableMovementTimerHandle, this, &AMainCharacter::EnableMovement, 1.0f, false);
			
		}
		//Staff + fire
		else if(SelectedSkill == EElementTag::E_Fire && SelectedWeapon == EWeaponType::E_Staff)
		{
			GetWorldTimerManager().SetTimer(ShootingAirTimerHandle, this, &AMainCharacter::ShootingSpellSkill, 0.3f, false);
			bIsShootingAir = true;
			GetCharacterMovement()->DisableMovement();
			GetWorldTimerManager().SetTimer(DisableMovementTimerHandle, this, &AMainCharacter::EnableMovement, 0.3f, false);
		
		}
		//Staff + water
		else if(SelectedSkill == EElementTag::E_Water && SelectedWeapon == EWeaponType::E_Staff)
		{
			
		}
		// Sword + air
		else if(SelectedSkill == EElementTag::E_Air && SelectedWeapon == EWeaponType::E_Sword)
		{
			// Implement sword + air skill
			GetWorldTimerManager().SetTimer(SwordDashTimerHandle, this, &AMainCharacter::SwordDash, 0.4f, false);
			bSwordDash = true;
			GetCharacterMovement()->DisableMovement();
			GetWorldTimerManager().SetTimer(DisableMovementTimerHandle, this, &AMainCharacter::EnableMovement, 0.4f, false);
		}
		// Sword + earth
		else if(SelectedSkill == EElementTag::E_Earth && SelectedWeapon == EWeaponType::E_Sword)
		{
			GetWorldTimerManager().SetTimer(StoneSwordTimerHandle, this, &AMainCharacter::StoneSwordSkill, 0.3f, false);
			bSwordRising = true;
			GetSprite()->SetFlipbook(StoneSwordAnimation);
			GetCharacterMovement()->DisableMovement();
			GetWorldTimerManager().SetTimer(DisableMovementTimerHandle, this, &AMainCharacter::EnableMovement, 0.3f, false);
			
			
			
		}
		// Sword + fire
		else if(SelectedSkill == EElementTag::E_Fire && SelectedWeapon == EWeaponType::E_Sword)
		{
			// Implement sword + fire skill
		}
		// Sword + water
		else if(SelectedSkill == EElementTag::E_Water && SelectedWeapon == EWeaponType::E_Sword)
		{
			WaterSwordSlice();
		}
	}
}

void AMainCharacter::ShootingSpellSkill()
{
	if (SpellClass)
	{
       bIsShootingAir = false;
		// +1 = right, -1 = left
		float FacingDirection = FMath::Sign(GetSprite()->GetRelativeScale3D().X);

		// Distance in front of the character
		const float ForwardOffset = 130.f;

		FVector SpawnLocation =
			GetActorLocation() +
			FVector(ForwardOffset * FacingDirection, 0.f, 0.f);

		FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		ASpell* Projectile = GetWorld()->SpawnActor<ASpell>(
			SpellClass,
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

void AMainCharacter::EarthWallSkill()
{
	if (EarthWallClass)
	{
		bWallRising = true;
		FVector SpawnLocation = GetActorLocation() - FVector(0,0,110);
		FVector FacingOffset = GetActorForwardVector() * 100.0f; // Adjust distance
		SpawnLocation += FacingOffset;

		FRotator SpawnRotation = FRotator::ZeroRotator;
		GetWorld()->SpawnActor<AActor>(EarthWallClass, SpawnLocation, SpawnRotation);
		
	}
	bWallRising = false;
}

void AMainCharacter::StoneSwordSkill()
{
	if (bSwordRising)
	{
		bSwordRising = false;
		if (!StoneRiftBulletClass) return;

		FVector ActorLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;

		// How far from the character center
		const float SideOffset = 60.f;

		// RIGHT spawn location
		FVector RightSpawnLocation = ActorLocation + FVector(SideOffset, 0.f, 0.f) - FVector(0,0,50);
		AStoneRiftBullet* RightProjectile =GetWorld()->SpawnActor<AStoneRiftBullet>(StoneRiftBulletClass,RightSpawnLocation,SpawnRotation);
		RightProjectile->SetMoveDirection(1.f); // move right
		
		

		
		
	}
}


void AMainCharacter::TapShield()
{
	bShieldActive = true;
	GetWorldTimerManager().SetTimer(
		ShieldTimerHandle,
		[this]()
		{
			bShieldActive = false;
		},
		ShieldDuration,
		false
	);
}

AActor* AMainCharacter::NearestEnemy(FVector2D Origin)
{
	float ClosestDistSq = FLT_MAX;
	AActor* NearestEnemy = nullptr;

	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), Enemies);

	for (AActor* Enemy : Enemies)
	{
		FVector2D EnemyLocation2D(Enemy->GetActorLocation().X, Enemy->GetActorLocation().Y);
		float DistSq = FVector2D::DistSquared(Origin, EnemyLocation2D);

		if (DistSq < ClosestDistSq)
		{
			ClosestDistSq = DistSq;
			NearestEnemy = Enemy;
		}
	}

	return NearestEnemy;
	
}
void AMainCharacter::WaterSwordSlice()
{
	FVector SpawnLocation = GetActorLocation() + FVector(80,0,0); // or weapon socket
	FRotator SpawnRotation = FRotator::ZeroRotator;

	AWaterSwordSlice* Projectile = GetWorld()->SpawnActor<AWaterSwordSlice>(WaterSwordSliceClass, SpawnLocation, SpawnRotation);

	if (Projectile)
	{
		FVector2D MyLocation2D(SpawnLocation.X, SpawnLocation.Y);
		AActor* MyNearestEnemy = NearestEnemy(MyLocation2D);

		if (MyNearestEnemy)
		{
			Projectile->SetDirection(MyNearestEnemy);
		}
	}
}

void AMainCharacter::SwordDash()
{
	if (bSwordDash)
	{
		bSwordDash = false;
		FVector Start = GetActorLocation();

		// Left / Right only
		float Direction = GetActorForwardVector().X >= 0.f ? 1.f : -1.f;
		FVector DashDir(Direction, 0.f, 0.f);

		FVector End = Start + DashDir * 800.f;

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			ECC_Pawn,
			Params
		);

		FVector TargetLocation = End;
		AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());

		if (bHit && Enemy)
		{
			TargetLocation = Hit.Location - DashDir * 80.f;
		}

		// Lock to 2D plane
		TargetLocation.Y = Start.Y;
		TargetLocation.Z = Start.Z;

		// Stop movement before teleport
		GetCharacterMovement()->StopMovementImmediately();

		// Teleport WITHOUT sweep (important for 2D dash)
		SetActorLocation(TargetLocation, false);

		// Force dash animation
		if (SwordDashAnimation)
		{
			GetSprite()->SetFlipbook(SwordDashAnimation);
			GetSprite()->PlayFromStart();
		}
		
	}
	
	
}


void AMainCharacter::EnableMovement()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}


void AMainCharacter::ShowSkillWheel()
{
	bIsSkillWheelVisible = true;

	// Slow down time
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);

	// Always create SkillWheel if it's not created yet
	if (!SkillWheelWidget && SkillWheelWidgetClass)
	{
		SkillWheelWidget = CreateWidget<USkillWheelWidget>(GetWorld(), SkillWheelWidgetClass);
		if (SkillWheelWidget)
		{
			SkillWheelWidget->AddToViewport();
			SkillWheelWidget->OnSkillSelected.AddDynamic(this, &AMainCharacter::OnSkillSelected);
		}
	}

	// Always create WeaponWheel if it's not created yet
	UE_LOG(LogTemp, Warning, TEXT("WeaponWheelWidget = %s"), WeaponWheelWidget ? TEXT("Valid") : TEXT("NULL"));
	UE_LOG(LogTemp, Warning, TEXT("WeaponWheelWidgetClass = %s"), WeaponWheelWidgetClass ? TEXT("Valid") : TEXT("NULL"));
	if (!WeaponWheelWidget && WeaponWheelWidgetClass)
	{
		WeaponWheelWidget = CreateWidget<UWeaponWheelWidget>(GetWorld(), WeaponWheelWidgetClass);
		if (WeaponWheelWidget)
		{
			WeaponWheelWidget->AddToViewport();
			WeaponWheelWidget->OnWeaponSelected.AddDynamic(this, &AMainCharacter::OnWeaponSelected);
		}
	}

	// Set visibility for both widgets
	if (SkillWheelWidget)
	{
		SkillWheelWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WeaponWheelWidget)
	{
		WeaponWheelWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void AMainCharacter::HideSkillWheel()
{
	bIsSkillWheelVisible = false;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	if ((SkillWheelWidget) && (WeaponWheelWidget))
	{
		SkillWheelWidget->SetVisibility(ESlateVisibility::Hidden);
		WeaponWheelWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainCharacter::OnSkillSelected(EElementTag SelectedSkill)
{
	CurrentSkill = SelectedSkill;
	if (MainSkillWidget)
	{
		MainSkillWidget->UpdateSkillIcon(SelectedSkill);
	}
}

void AMainCharacter::OnWeaponSelected(EWeaponType SelectedWeapon)
{
	CurrentWeapon = SelectedWeapon;
	if(MainWeaponWidget)
	{
		MainWeaponWidget->UpdateWeaponIcon(SelectedWeapon);
	}
}

void AMainCharacter::SelectSkillLeft()
{
	if (bIsSkillWheelVisible)
		OnSkillSelected(EElementTag::E_Water);

}

void AMainCharacter::SelectSkillRight()
{
	if (bIsSkillWheelVisible)
		OnSkillSelected(EElementTag::E_Fire);
}

void AMainCharacter::SelectSkillUp()
{
	if (bIsSkillWheelVisible)
		OnSkillSelected(EElementTag::E_Earth);
}

void AMainCharacter::SelectSkillDown()
{
	if (bIsSkillWheelVisible)
		OnSkillSelected(EElementTag::E_Air);
}

void AMainCharacter::SelectWeaponLeft()
{
	if(bIsSkillWheelVisible)
	{
		OnWeaponSelected(EWeaponType::E_Staff);
	}
}

void AMainCharacter::SelectWeaponRight()
{
	if(bIsSkillWheelVisible)
	{
		OnWeaponSelected(EWeaponType::E_Sword);
	}
}

void AMainCharacter::SelectWeaponUp()
{
	if(bIsSkillWheelVisible)
	{
		OnWeaponSelected(EWeaponType::E_Bow);
	}
}

void AMainCharacter::SelectWeaponDown()
{
	if(bIsSkillWheelVisible)
	{
		OnWeaponSelected(EWeaponType::E_Spear);
	}
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateAnimation();
	CheckIsJumping();
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	if (MainSkillWidgetClass)
	{
		MainSkillWidget = CreateWidget<UMainSkillWidget>(GetWorld(), MainSkillWidgetClass);
		if (MainSkillWidget)
		{
			MainSkillWidget->AddToViewport();
			MainSkillWidget->UpdateSkillIcon(CurrentSkill);
		}
	}
	if (MainWeaponWidgetClass)
	{
		MainWeaponWidget = CreateWidget<UMainWeaponWidget>(GetWorld(), MainWeaponWidgetClass);
		if (MainWeaponWidget)
		{
			MainWeaponWidget->AddToViewport();
			MainWeaponWidget->UpdateWeaponIcon(CurrentWeapon);
		}
		
	}
}


void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Started, this, &AMainCharacter::ActivateSkill);
		EnhancedInputComponent->BindAction(Block, ETriggerEvent::Started, this, &AMainCharacter::TapShield);

		EnhancedInputComponent->BindAction(SkillWheelAction, ETriggerEvent::Started, this, &AMainCharacter::ShowSkillWheel);
		EnhancedInputComponent->BindAction(SkillWheelAction, ETriggerEvent::Completed, this, &AMainCharacter::HideSkillWheel);

		//Skill Selection
		EnhancedInputComponent->BindAction(SkillWheelSelectAction, ETriggerEvent::Started, this, &AMainCharacter::SelectSkillLeft);
		EnhancedInputComponent->BindAction(SkillWheelSelectAction2, ETriggerEvent::Started, this, &AMainCharacter::SelectSkillRight);
		EnhancedInputComponent->BindAction(SkillWheelSelectAction3, ETriggerEvent::Started, this, &AMainCharacter::SelectSkillUp);
		EnhancedInputComponent->BindAction(SkillWheelSelectAction4, ETriggerEvent::Started, this, &AMainCharacter::SelectSkillDown);
		//Weapon Selection
		EnhancedInputComponent->BindAction(WeaponWheelSelectActionLeft, ETriggerEvent::Started, this, &AMainCharacter::SelectWeaponLeft);
		EnhancedInputComponent->BindAction(WeaponWheelSelectActionRight, ETriggerEvent::Started, this, &AMainCharacter::SelectWeaponRight);
		EnhancedInputComponent->BindAction(WeaponWheelSelectActionUp, ETriggerEvent::Started, this, &AMainCharacter::SelectWeaponUp);
		EnhancedInputComponent->BindAction(WeaponWheelSelectDown, ETriggerEvent::Started, this, &AMainCharacter::SelectWeaponDown);
	}
		
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	if (bIsSkillWheelVisible)
		return;
	float MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		if (MovementValue != 0.0f)
		{
			
			// Move only along X axis
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementValue);
			if (MovementValue < 0)
			{
				GetSprite()->SetRelativeScale3D(FVector(-0.5f, 0.5f, 0.5f)); // Flip horizontally (face left)
			}
			else if (MovementValue > 0)
			{
				GetSprite()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f)); // Default (face right)
			}
		}
		
	}
}


