// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Boss1.h"
#include "MainCharacter.h"
#include "ElderAIController.generated.h"

/**
 * 
 */
UCLASS()
class VIETRPG_API AElderAIController : public AAIController
{
	GENERATED_BODY()
public:
	AElderAIController();

	void BeginPlay() override;
	void OnPossess(APawn* InPawn) override;

	UBlackboardComponent* GetBlackboardComp() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBlackboardComponent* BlackboardComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBehaviorTreeComponent* BehaviorTreeComponent;
	
	UPROPERTY(EditAnywhere)
	UBlackboardData* AIBlackboard;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere)
	AMainCharacter* TargetPlayer;

	void Shoot();
	void BossMeditate();
	void FireSlam();
};
