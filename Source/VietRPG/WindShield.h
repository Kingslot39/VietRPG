// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EarthWall.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WindShield.generated.h"

UCLASS()
class VIETRPG_API AWindShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindShield();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Wind Shield")
	UBoxComponent* ShieldBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Shield")
	UPaperSprite* ShieldSprite;
	UFUNCTION()
	void OnShieldHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
