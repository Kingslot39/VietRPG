// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "ElderStoneRift.generated.h"

UCLASS()
class VIETRPG_API AElderStoneRift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElderStoneRift();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UPaperFlipbookComponent* SpellSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 2.0f;

	float MoveDirection = 1.f;

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;
	

	void SetMoveDirection(float Direction);
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
