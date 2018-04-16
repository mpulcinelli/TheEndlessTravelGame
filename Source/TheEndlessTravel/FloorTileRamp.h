// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FloorTile.h"
#include "CoreMinimal.h"
#include "FloorTileRamp.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API AFloorTileRamp : public AFloorTile
{
	GENERATED_BODY()

public:
	AFloorTileRamp();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RampMeshComponent;

public:
	virtual FTransform GetAttachTransform() override;
};