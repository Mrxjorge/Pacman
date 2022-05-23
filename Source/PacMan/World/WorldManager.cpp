// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "Floor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldManager::ResetWorldHeight() const 
{
	TArray<AActor*> FloorActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFloor::StaticClass(), FloorActors);
	for(AActor* Actor : FloorActors)
	{
		FVector CurrentLocation = Actor->GetActorLocation();
		CurrentLocation.Z = 0;
		Actor->SetActorLocation(CurrentLocation);
	}
}

void AWorldManager::SubscribeFloor(AFloor* InFloor)
{
	Floor.Add(InFloor);
}

void AWorldManager::SubscribeCharacter(APacManCharacter* InCharacter)
{
	Character = InCharacter;
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	TArray<AActor*> FloorActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFloor::StaticClass(), FloorActors);
	for (AActor* F : FloorActors)
	{
		Floor.Add(Cast<AFloor>(F));
	}
	Super::BeginPlay();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AWorldManager* AWorldManager::GetWorldManager(UObject* Context)
{
	TArray<AActor*> Array;
	UGameplayStatics::GetAllActorsOfClass(Context, AWorldManager::StaticClass(), Array);
	if(Array.Num() == 0) return nullptr;
	return  Cast<AWorldManager>(Array[0]);
}

