// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostController.h"

#include "GhostCharacter.h"
#include "PacMan/PacManCharacter.h"

void AGhostController::ChasePlayer(AActor* Player)
{
	MoveToActor(Player);
}

void AGhostController::GoToLocation(FVector Location)
{
	MoveToLocation(Location);
}

void AGhostController::Initialize(const EGhostType InType)
{
	GhostType = InType;
	AGhostCharacter* Ghost = Cast<AGhostCharacter>(GetPawn());
	Ghost->OnGhostReachedPlayer.BindLambda([=]()
	{
		OnObjectiveReached.Broadcast(GhostType);
	});
}
