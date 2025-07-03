// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElementCombineComponent.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	E_Staff UMETA(DisplayName = "Staff"),
	E_Sword UMETA(DisplayName = "Sword"),
	E_Bow   UMETA(DisplayName = "Bow"),
	E_Spear  UMETA(DisplayName = "Axe"),
};
UCLASS()
class VIETRPG_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EElementTag ElementTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName AttachSocketName;
	UPROPERTY(EditAnywhere,Blueprintable, Category = "Weapon")
	UPaperSprite* WeaponSprite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponName;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
