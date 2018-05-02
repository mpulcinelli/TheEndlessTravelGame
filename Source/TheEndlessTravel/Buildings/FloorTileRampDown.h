// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FloorTile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTileRampDown.generated.h"

UCLASS()
class THEENDLESSTRAVEL_API AFloorTileRampDown : public AFloorTile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTileRampDown();

protected:

	class UMaterial* RampMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RampMeshComponent;

public:
	virtual FTransform GetAttachTransform() override;

};
