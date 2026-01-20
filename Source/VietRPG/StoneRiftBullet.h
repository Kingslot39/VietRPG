// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "ElementCombineComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "StoneRiftBullet.generated.h"

UCLASS()
class VIETRPG_API AStoneRiftBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneRiftBullet();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UPaperFlipbookComponent* SpellSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTag ElementTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 2.0f;

	float MoveDirection = 1.f;

	UPROPERTY(EditAnywhere)
	float Speed = 1200.f;
	

	void SetMoveDirection(float Direction);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UElementCombineComponent* ElementCombineComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
