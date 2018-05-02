// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/FloorTile.h"
#include "FloorTileTunnel.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API AFloorTileTunnel : public AFloorTile
{
	GENERATED_BODY()

public:

	AFloorTileTunnel();

	virtual FTransform GetAttachTransform() override;

protected:

	class UMaterial* CeilingMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CeilingMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* CeilingLightComponent;

	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	
};
