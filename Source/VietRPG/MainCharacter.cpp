// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
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
			}
		}
}


void AMainCharacter::ActivateSkill()
{
	if(MainSkillWidget)
	{
		EElementTag SelectedSkill = MainSkillWidget->GetCurrentSkillTag();
		switch (SelectedSkill)
		{
			case  EElementTag::E_Water:
				// Activate Water skill
				UE_LOG(LogTemp, Warning, TEXT("Water skill activated!"));
				break;
			case EElementTag::E_Fire:
				// Activate Fire skill
				UE_LOG(LogTemp, Warning, TEXT("Fire skill activated!"));
			    ShootingSpellSkill();
				break;
			case  EElementTag::E_Earth:
				// Activate Earth skill
				UE_LOG(LogTemp, Warning, TEXT("Earth skill activated!"));
			    EarthWallSkill();
				break;
			case  EElementTag::E_Air:
				// Activate Air skill
				UE_LOG(LogTemp, Warning, TEXT("Air skill activated!"));
				break;
		}
	}
}

void AMainCharacter::ShootingSpellSkill()
{
	if (SpellClass)
	{
		float FacingDirection = GetSprite()->GetRelativeScale3D().X;
		FVector Offset = FVector(50.f * FacingDirection, 0.f, 0.f);
		FVector SpawnLocation = GetActorLocation() + Offset;
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

void AMainCharacter::ShowSkillWheel()
{
	bIsSkillWheelVisible = true;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0.1);
	if ((!SkillWheelWidget && SkillWheelWidgetClass)&&(!WeaponWheelWidget && WeaponWheelWidgetClass))
	{
		SkillWheelWidget = CreateWidget<USkillWheelWidget>(GetWorld(), SkillWheelWidgetClass);
		if (SkillWheelWidget)
		{
			SkillWheelWidget->AddToViewport();
			SkillWheelWidget->OnSkillSelected.AddDynamic(this, &AMainCharacter::OnSkillSelected);
		}
		WeaponWheelWidget = CreateWidget<UWeaponWheelWidget>(GetWorld(), WeaponWheelWidgetClass);
		if (WeaponWheelWidget)
		{
			WeaponWheelWidget->AddToViewport();
			WeaponWheelWidget->OnWeaponSelected.AddDynamic(this, &AMainCharacter::OnWeaponSelected);
		}
	}
	else if ((WeaponWheelWidget) && (SkillWheelWidget))
	{
		SkillWheelWidget->SetVisibility(ESlateVisibility::Visible);
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
				GetSprite()->SetRelativeScale3D(FVector(-1.f, 1.f, 1.f)); // Flip horizontally (face left)
			}
			else if (MovementValue > 0)
			{
				GetSprite()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f)); // Default (face right)
			}
		}
		
	}
}


