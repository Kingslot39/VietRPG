// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementCombineComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Spell.generated.h"

UCLASS()
class VIETRPG_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UPaperFlipbookComponent* SpellSprite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTag ElementTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 2.0f;

	void SetDirection(float Direction);


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UElementCombineComponent* ElementCombineComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
