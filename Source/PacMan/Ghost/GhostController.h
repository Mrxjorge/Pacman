// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GhostController.generated.h"

UENUM()
enum class EGhostType : uint8
{
	Wanderer,
	Chaser
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveReached, const EGhostType, Type);

/**
 * 
 */
UCLASS()
class PACMAN_API AGhostController : public AAIController
{
	GENERATED_BODY()

public:

	void ChasePlayer(AActor* Player);

	void GoToLocation(FVector Location);
	
	FOnObjectiveReached OnObjectiveReached;

	EGhostType GhostType = EGhostType::Wanderer;

	void Initialize(const EGhostType InType);
	
};
