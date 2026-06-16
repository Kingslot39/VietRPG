// Fill out your copyright notice in the Description page of Project Settings.


#include "ElderAIController.h"

#include "BehaviorTree/BehaviorTree.h"

AElderAIController::AElderAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void AElderAIController::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	RunBehaviorTree(BehaviourTree);
	BehaviorTreeComponent->StartTree(*BehaviourTree);
}

void AElderAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(BlackboardComponent){
		Blackboard->InitializeBlackboard(*BehaviourTree->BlackboardAsset);	
	}
}

UBlackboardComponent* AElderAIController::GetBlackboardComp() const
{
	return BlackboardComponent;
}

void AElderAIController::Shoot()
{
	ABoss1* Boss1 = Cast<ABoss1>(GetPawn());
	if(Boss1)
	{
		Boss1->ShootTwice();
	}
}

void AElderAIController::BossMeditate()
{
  	ABoss1* Boss1 = Cast<ABoss1>(GetPawn());
	if(Boss1)
	{
		Boss1->Meditate();
	}
}

void AElderAIController::FireSlam()
{
	ABoss1* Boss1 = Cast<ABoss1>(GetPawn());
	if(Boss1)
	{
		Boss1->FireStep();
	}
}

void AElderAIController::OnBossPhase2Activated()
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsBool(FName("bIsPhase2"), true);
	}
}
