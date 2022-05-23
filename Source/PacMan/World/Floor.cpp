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
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComponent->SetupAttachment(Form);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 100));
	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	Collectable = CreateDefaultSubobject<UStaticMeshComponent>("Collectable");
	Collectable->SetupAttachment(BoxComponent);
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

void AFloor::ControlColllectable(const bool Visibility, const ECollectable Type)
{
	Collectable->SetVisibility(Visibility);
	if(!Visibility)return;
	switch (Type)
	{
		case ECollectable::Normal:
			Collectable->SetMaterial(0, NormalCollectable);
			break;
		case ECollectable::Special:
			Collectable->SetMaterial(0, SpecialCollectable);
			break;
		default:
			break;
	}
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

