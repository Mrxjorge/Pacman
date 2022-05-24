// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor.h"
#include "GameFramework/Actor.h"
#include "PacMan/PacManCharacter.h"
#include "PacMan/Ghost/GhostCharacter.h"
#include "PacMan/Ghost/GhostController.h"
#include "WorldManager.generated.h"

USTRUCT()
struct FGhostHandle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	AGhostController* Controller;

	UPROPERTY()
	AGhostCharacter* Character;

	FGhostHandle(AGhostCharacter* InCharacter, AGhostController* InController)
	{
		this->Controller = InController;
		this->Character = InCharacter;
	}
	
	FGhostHandle()
	{
		this->Controller = nullptr;
		this->Character = nullptr;
	}
	
};

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGhostCharacter> GhostClass;

	UPROPERTY()
	TArray<FGhostHandle> Ghosts;

	AGhostController* SpawnGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	USceneComponent* Root = nullptr;

	int PointsCount = 0;
	
};
