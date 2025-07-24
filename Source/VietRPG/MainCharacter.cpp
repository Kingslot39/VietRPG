// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"


AMainCharacter::AMainCharacter()
{
	
}


void AMainCharacter::Jump()
{
	Super::Jump();
	if (JumpAnimation && GetSprite()->GetFlipbook() != JumpAnimation)
	{
		GetSprite()->SetFlipbook(JumpAnimation);
	}
}


void AMainCharacter::Landed(const FHitResult& Hit)
{
		Super::Landed(Hit);

		if (LandingAnimation && GetSprite()->GetFlipbook() != LandingAnimation)
		{
			GetSprite()->SetFlipbook(LandingAnimation);
		}

		// Delay return to idle/walk after landing animation duration
		GetWorldTimerManager().SetTimer(
			LandingDelayHandle,
			this,
			&AMainCharacter::UpdateAnimation,
			0.2, // Length of your landing animation
			false
		);
}


void AMainCharacter::UpdateAnimation()
{
		// If in air
		if (GetCharacterMovement()->IsFalling())
		{
			if (JumpAnimation && GetSprite()->GetFlipbook() != JumpAnimation)
			{
				GetSprite()->SetFlipbook(JumpAnimation);
				GetSprite()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
			}
		}

		// Not falling = on ground
		// Avoid overwriting LandingAnimation too soon
		if (GetWorldTimerManager().IsTimerActive(LandingDelayHandle))
		{
			return; // Wait until landing animation finishes
		}

		float Speed = GetVelocity().SizeSquared();

		if (Speed > 0.0f)
		{
			if (WalkAnimation && GetSprite()->GetFlipbook() != WalkAnimation)
			{
				GetSprite()->SetFlipbook(WalkAnimation);
			}
		}
		else
		{
			if (IdleAnimation && GetSprite()->GetFlipbook() != IdleAnimation)
			{
				GetSprite()->SetFlipbook(IdleAnimation);
				GetSprite()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
				
			}
		}
}


void AMainCharacter::ActivateSkill()
{
	if(MainSkillWidget)
	{
		EElementTag SelectedSkill = MainSkillWidget->GetCurrentSkillTag();
		EWeaponType SelectedWeapon = MainWeaponWidget->GetCurrentWeaponType();
		// Staff + air
		if(SelectedSkill == EElementTag::E_Air && SelectedWeapon == EWeaponType::E_Staff)
		{
			WindShieldSkill();
		}
		//Staff + earth
		else if(SelectedSkill == EElementTag::E_Earth && SelectedWeapon == EWeaponType::E_Staff)
		{
			EarthWallSkill();
		}
		//Staff + fire
		else if(SelectedSkill == EElementTag::E_Fire && SelectedWeapon == EWeaponType::E_Staff)
		{
			ShootingSpellSkill();
		}
		//Staff + water
		else if(SelectedSkill == EElementTag::E_Water && SelectedWeapon == EWeaponType::E_Staff)
		{
			
		}
		// Sword + air
		else if(SelectedSkill == EElementTag::E_Air && SelectedWeapon == EWeaponType::E_Sword)
		{
			// Implement sword + air skill
		}
		// Sword + earth
		else if(SelectedSkill == EElementTag::E_Earth && SelectedWeapon == EWeaponType::E_Sword)
		{
			
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
		float FacingDirection = GetSprite()->GetRelativeScale3D().X;
		FVector Offset = FVector(50.f * FacingDirection, 0.f, 0.f);
		FVector SpawnLocation = GetActorLocation() + Offset + FVector(80,0,0);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		ASpell* Projectile = GetWorld()->SpawnActor<ASpell>(SpellClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (Projectile)
		{
			Projectile->SetDirection(FacingDirection);
		}
	}
}

void AMainCharacter::EarthWallSkill()
{
	FVector SpawnLocation = GetActorLocation() - FVector(0,0,100);
	FVector FacingOffset = GetActorForwardVector() * 100.0f; // Adjust distance
	SpawnLocation += FacingOffset;

	FRotator SpawnRotation = FRotator::ZeroRotator;

	GetWorld()->SpawnActor<AActor>(EarthWallClass, SpawnLocation, SpawnRotation);
}

void AMainCharacter::WindShieldSkill()
{
	if(WindShieldClass)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		AWindShield* WindShield = GetWorld()->SpawnActor<AWindShield>(WindShieldClass, SpawnLocation, SpawnRotation);
		if (WindShield)
		{
			WindShield->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn WindShield"));
		}
	}
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
				GetSprite()->SetRelativeScale3D(FVector(-0.3f, 0.3f, 0.3f)); // Flip horizontally (face left)
			}
			else if (MovementValue > 0)
			{
				GetSprite()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f)); // Default (face right)
			}
		}
		
	}
}


