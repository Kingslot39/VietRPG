// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElderStoneRift.h"
#include "ElderWaterSphere.h"
#include "ElderWindSphere.h"
#include "Enemy.h"
#include "FireColumn.h"
#include "MainCharacter.h"
#include "Boss1.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEnemySkill : uint8
{
	None,
	AirShooting,
	Meditate,
	FireSlam,
	// ...
};

UCLASS()
class VIETRPG_API ABoss1 : public AEnemy
{
	GENERATED_BODY()
public:
	ABoss1();

	void UpdateAnimation() ;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	AMainCharacter* Target;

	// Air Shooting Skill
	void AirShootingSkill();
	UPROPERTY(EditAnywhere,BLueprintreadwrite)
	bool bIsShootingAir = false;
	UFUNCTION(BlueprintCallable)
	void ShootTwice();
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	TSubclassOf<AElderWindSphere> ElderWindSphereClass;
	FTimerHandle ShootTimerHandle;
	FTimerHandle ResetAniTimeHandle;

	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	UPaperFlipbook* AirSphereShootingAnimation;

	// Skill transaction
	FTimerHandle SkillTransactionTimerHandle;
	// Stone Rift Jump
	void SlamDown();
	void StoneRiftJump();
	void StoneShootTwice();
	void StoneRiftShoot();
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	bool bIsJumpingStone = false;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	TSubclassOf<AElderStoneRift> ElderStoneRiftClass;
	FTimerHandle ResetAniJumpTimerHandle;
    FTimerHandle StoneRiftJumpTimerHandle;
	FTimerHandle StoneShootTwiceTimerHandle;
	FTimerHandle SlamTimerHandle;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	UPaperFlipbook* StoneRiftJumpAnimation;

	// Meditate
	void Meditate();
	void SpawnTrap();
	UPROPERTY(EditAnywhere)
	float SpawnInterval = 3.f;

	UPROPERTY(EditAnywhere)
	int32 SpawnCountMax = 4;

	int32 CurrentSpawnCount = 0;

	FTimerHandle SpawnTimerHandle;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	UPaperFlipbook* MeditateAnimation;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	TSubclassOf<AElderWaterSphere> WaterSphereClass;
	bool bIsMeditating = false;

	//Fire Step
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFireColumn> FireColumnClass;
	// Spawn settings
	UPROPERTY(EditAnywhere)
	float ColumnSpacing = 200.f;
	UPROPERTY(EditAnywhere)
	float PillarSpawn = 0.2f;
	UPROPERTY(EditAnywhere)
	float WaveSpeed = 5000.f;

	UPROPERTY(EditAnywhere)
	int32 MaxColumns = 10;

	FTimerHandle FireColumnTimer;
    
	int32 CurrentColumnCount = 0;
	FVector CurrentSpawnLocation;
	FVector RockSpawnDirection;

	void FireStep();
	void CastFirePillar();
	void SpawnFireColumn();
	bool bIsCastingFirePillar = false;

	FTimerHandle FirePillarTimer;
	UPROPERTY(EditAnywhere,Blueprintreadwrite)
	UPaperFlipbook* FirePillarAnimation;
	FTimerHandle StopFirePillarTimer;
	void StopFirePillar();


private:
	void Tick(float DeltaSeconds) override;

	void BeginPlay() override;
	
	
	
	
};
