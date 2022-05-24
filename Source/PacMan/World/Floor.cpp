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
	RootComponent = Form;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComponent->SetupAttachment(Form);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 100));
	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	BoxComponent->SetGenerateOverlapEvents(true);
	Collectable = CreateDefaultSubobject<UStaticMeshComponent>("Collectable");
	Collectable->SetupAttachment(Form);
	Collectable->SetRelativeLocation(FVector(0, 0, 50));
	Collectable->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	AWorldManager::GetWorldManager(this)->SubscribeFloor(this);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFloor::BeginOverlap);
	ControlColllectable(false);
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
	bCollected = !Visibility;
	if(!Visibility)return;
	CollectableType = Type;
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

void AFloor::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	APacManCharacter* Character = Cast<APacManCharacter>(OtherActor);
	if(!Character) return;
	if(bCollected) return;
	ControlColllectable(false);
	Character->ControlPoints(CollectableType == ECollectable::Normal ? 1 : 5);
	bCollected = true;
}
