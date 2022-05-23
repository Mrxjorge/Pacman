// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UENUM(BlueprintType)
enum class ECollectable : uint8
{
	None,
	Normal,
	Special
};

UENUM()
enum class EForm : uint8
{
	Wall,
	Floor
};

UCLASS()
class PACMAN_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	EForm FormStatus = EForm::Floor;

	UPROPERTY()
	ECollectable CollectableTpe = ECollectable::None;

	UPROPERTY(EditAnywhere)
	UStaticMesh* WallForm = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* FloorForm = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterial* NormalCollectable = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterial* SpecialCollectable = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Form = nullptr;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Collectable = nullptr;

	UFUNCTION(BlueprintCallable)
	void UpdateFloor();

	void ControlColllectable(const bool Visibility, const ECollectable Type);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& E) override;

};
