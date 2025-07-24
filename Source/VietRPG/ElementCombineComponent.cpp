// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementCombineComponent.h"

#include "Enemy.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/CookEnums.h"

// Sets default values for this component's properties
UElementCombineComponent::UElementCombineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UElementCombineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UElementCombineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UElementCombineComponent::ApplyElement(EElementTag NewElementTag)
{
	if(FirstElementTag == EElementTag::E_None)
	{
		FirstElementTag = NewElementTag;
	}
	else if(SecondElementTag == EElementTag::E_None)
	{
		SecondElementTag = NewElementTag;
	}
	else
	{
		// Reset both elements if they are already set
		ResetElement();
		FirstElementTag = NewElementTag;
	}
}

void UElementCombineComponent::CheckComboEffect()
{
	TArray<AActor*> AffectedActors;
	float Radius = 500.f;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), AffectedActors);

	// Water + Fire
	if((FirstElementTag == EElementTag::E_Water && SecondElementTag == EElementTag::E_Fire) ||
	   (FirstElementTag == EElementTag::E_Fire && SecondElementTag == EElementTag::E_Water))
	{
		
		for (AActor* Actor : AffectedActors)
		{
			// You can also use Cast<AEnemy>(Actor) or Cast<ABoss>(Actor) if needed
			if (Actor->ActorHasTag("Enemy") || Actor->ActorHasTag("Boss"))
			{
				// Apply a custom effect, e.g., freeze for 5 seconds
				if (AEnemy* Enemy = Cast<AEnemy>(Actor))
				{
					Enemy->PosionSmokeStart(1.2, 5);
				}
				//else if (ABoss* Boss = Cast<ABoss>(Actor))
				//{
				//	Boss->ApplyFullFreeze(5.0f);
				//}
			}
		}
	}
	//Water + Earth
	else if((FirstElementTag == EElementTag::E_Water && SecondElementTag == EElementTag::E_Earth) ||
	        (FirstElementTag == EElementTag::E_Earth && SecondElementTag == EElementTag::E_Water))
	{
		// Apply Mud effect
		UE_LOG(LogTemp, Warning, TEXT("Freeze applied"));
		for (AActor* Actor : AffectedActors)
		{
			// You can also use Cast<AEnemy>(Actor) or Cast<ABoss>(Actor) if needed
			if (Actor->ActorHasTag("Enemy") || Actor->ActorHasTag("Boss"))
			{
				// Apply a custom effect, e.g., freeze for 5 seconds
				if (AEnemy* Enemy = Cast<AEnemy>(Actor))
				{
					Enemy->Freeze(5);
				}
				//else if (ABoss* Boss = Cast<ABoss>(Actor))
				//{
				//	Boss->ApplyFullFreeze(5.0f);
				//}
			}
		}
	}
	// Water + Air
	else if((FirstElementTag == EElementTag::E_Water && SecondElementTag == EElementTag::E_Air) ||
	        (FirstElementTag == EElementTag::E_Air && SecondElementTag == EElementTag::E_Water))
	{
		// Apply Mist effect
		UE_LOG(LogTemp, Warning, TEXT("Mist effect applied!"));
	}
	
	// Fire + Air
	else if((FirstElementTag == EElementTag::E_Fire && SecondElementTag == EElementTag::E_Air) ||
	        (FirstElementTag == EElementTag::E_Air && SecondElementTag == EElementTag::E_Fire))
	{
		// Apply Heat effect
		UE_LOG(LogTemp, Warning, TEXT("Heat effect applied!"));
	}
	// Fire + Earth
	else if((FirstElementTag == EElementTag::E_Fire && SecondElementTag == EElementTag::E_Earth) ||
	        (FirstElementTag == EElementTag::E_Earth && SecondElementTag == EElementTag::E_Fire))
	{
		// Apply Lava effect
		UE_LOG(LogTemp, Warning, TEXT("Lava effect applied!"));
	}
	// Earth + Air
	else if((FirstElementTag == EElementTag::E_Earth && SecondElementTag == EElementTag::E_Air) ||
	        (FirstElementTag == EElementTag::E_Air && SecondElementTag == EElementTag::E_Earth))
	{
		// Apply Dust effect
		UE_LOG(LogTemp, Warning, TEXT("Dust effect applied!"));
	}
	//Nothing happen
	else
	{
		// No valid combination found
		UE_LOG(LogTemp, Warning, TEXT("No valid element combination found."));
	}
}

void UElementCombineComponent::ResetElement()
{
	FirstElementTag = EElementTag::E_None;
	SecondElementTag = EElementTag::E_None;
	UE_LOG(LogTemp, Warning, TEXT("Elements reset to None."));
}

