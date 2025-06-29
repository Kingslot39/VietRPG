// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Controller.h"



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
}


void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
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


