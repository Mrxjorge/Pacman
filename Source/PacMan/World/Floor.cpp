// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "WorldManager.h"
#include "Components/BoxComponent.h"

// Sets default values
AFloor::AFloor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Form = CreateDefaultSubobject<UStaticMeshComponent>("Form");
	Form->SetupAttachment(RootComponent);
	Collectable = CreateDefaultSubobject<UStaticMeshComponent>("Collectable");
	Collectable->SetupAttachment(Form);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComponent->SetupAttachment(Collectable);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));
	BoxComponent->SetBoxExtent(FVector(50, 50, 50));
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	AWorldManager::GetWorldManager(this)->SubscribeFloor(this);
	Super::BeginPlay();
}

void AFloor::PostEditChangeProperty(FPropertyChangedEvent& E)
{
	const FName Property = (E.Property != NULL) ? E.GetPropertyName() : NAME_None;
	if(Property == FName(TEXT("FormStatus")))
	{
		UpdateFloor();
	}
	Super::PostEditChangeProperty(E);
}

void AFloor::UpdateFloor()
{
	if(FormStatus == EForm::Wall)
	{
		if(WallForm)
		{
			Form->SetStaticMesh(WallForm);
			Form->AddWorldOffset(FVector(0, 0, 50));
		}
	}
	else
	{
		if(FloorForm)
		{
			Form->SetStaticMesh(FloorForm);
			Form->AddWorldOffset(FVector(0, 0, -50));
		}
	}
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

