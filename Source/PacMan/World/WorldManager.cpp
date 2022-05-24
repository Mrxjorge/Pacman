// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "Floor.h"
#include "Kismet/GameplayStatics.h"
#include "PacMan/Ghost/GhostCharacter.h"
#include "PacMan/Ghost/GhostController.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
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

void AWorldManager::ActivateAllNormalCollectables()
{
	TArray<AActor*> FloorActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFloor::StaticClass(), FloorActors);
	for(AActor* Actor : FloorActors)
	{
		AFloor* F = Cast<AFloor>(Actor);
		F->ControlColllectable(true, ECollectable::Normal);
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
	FTimerHandle TH;
	GetWorld()->GetTimerManager().SetTimer(TH, [=]()
	{
		int Num = FMath::RandRange(0, Floor.Num() - 1);
		if(Floor[Num]->FormStatus == EForm::Wall || Floor[Num]->bIsGhostSpawn) return;
		Floor[Num]->ControlColllectable(true, PointsCount >= 20 ? ECollectable::Special : ECollectable::Normal);
		PointsCount = PointsCount >= 20 ? 0 : PointsCount + 1;
	}, 1.f, true);
	FTimerHandle TH2;
	GetWorld()->GetTimerManager().SetTimer(TH2, [=]()
	{
		SpawnGhost();
	}, 15, true);
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

AGhostController* AWorldManager::SpawnGhost()
{
	if(Ghosts.Num() >= 2) return nullptr;
	auto CreateGhost = [=]()
	{
		FVector SpawnLocation = GetActorLocation();
		AGhostCharacter* Ghost = Cast<AGhostCharacter>(GetWorld()->SpawnActor(GhostClass, &SpawnLocation, &FRotator::ZeroRotator, FActorSpawnParameters()));
		AGhostController* Controller = Ghost->GetController<AGhostController>();
		return FGhostHandle(Ghost, Controller);
	};
	FGhostHandle Ghost = CreateGhost();
	if(Ghosts.Num() == 0)
	{
		Ghosts.Add(Ghost);
	}
	else if(Ghosts.Num() == 1)
	{
		Ghosts.Add(Ghost);
	}
	return  Ghost.Controller;
}

