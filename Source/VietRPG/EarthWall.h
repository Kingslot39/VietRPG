// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "EarthWall.generated.h"

UCLASS()
class VIETRPG_API AEarthWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEarthWall();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Earth Wall")
	UPaperFlipbookComponent* EarthWallSprite;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UBoxComponent* Collision;

	FTimerHandle Timer;

	void EnableCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
