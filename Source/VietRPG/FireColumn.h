// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireColumn.generated.h"

UCLASS()
class VIETRPG_API AFireColumn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireColumn();
	UPROPERTY(EditAnywhere,BlueprintReadwrite)
	FTimerHandle SpawnTimerHandle;
	void DestroyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
