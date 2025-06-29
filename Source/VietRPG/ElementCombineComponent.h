// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementCombineComponent.generated.h"

UENUM(BlueprintType)
enum class EElementTag : uint8
{
	E_None  UMETA(DisplayName = "None"),
	E_Fire  UMETA(DisplayName = "Fire"),
	E_Water UMETA(DisplayName = "Water"),
	E_Earth UMETA(DisplayName = "Earth"),
	E_Air   UMETA(DisplayName = "Air"),
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIETRPG_API UElementCombineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElementCombineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Element Combine")
	EElementTag FirstElementTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Element Combine")
	EElementTag SecondElementTag;

	UFUNCTION(BlueprintCallable, Category = "Element Combine")
	void ApplyElement(EElementTag NewElementTag);

	void CheckComboEffect();
	void ResetElement();	

		
};
