// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor.h"
#include "GameFramework/Actor.h"
#include "PacMan/PacManCharacter.h"
#include "WorldManager.generated.h"

UCLASS()
class PACMAN_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

	UPROPERTY()
	TArray<AFloor*> Floor;

	UPROPERTY()
	APacManCharacter* Character;

	UFUNCTION(CallInEditor)
	void ResetWorldHeight() const;

	UFUNCTION(CallInEditor)
	void ActivateAllNormalCollectables();

	void SubscribeFloor(AFloor* InFloor);

	void SubscribeCharacter(APacManCharacter* InCharacter);

	virtual void Tick(float DeltaTime) override;

	static AWorldManager* GetWorldManager(UObject* Context);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
