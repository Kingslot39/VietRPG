// Fill out your copyright notice in the Description page of Project Settings.


#include "WindShield.h"
#include "PaperSprite.h"

// Sets default values
AWindShield::AWindShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShieldBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldBox"));
	RootComponent = ShieldBox;
	ShieldBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ShieldBox->SetGenerateOverlapEvents(true);


	ShieldSprite = CreateDefaultSubobject<UPaperSprite>(TEXT("ShieldSprite"));
	
	

}

void AWindShield::OnShieldHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

// Called when the game starts or when spawned
void AWindShield::BeginPlay()
{
	Super::BeginPlay();
	ShieldBox->OnComponentBeginOverlap.AddDynamic(this, &AWindShield::OnShieldHit);
}

// Called every frame
void AWindShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

