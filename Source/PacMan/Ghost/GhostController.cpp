// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostController.h"

void AGhostController::ChasePlayer(AActor* Player)
{
	MoveToActor(Player);
}

void AGhostController::GoToLocation(FVector Location)
{
	MoveToLocation(Location);
}
