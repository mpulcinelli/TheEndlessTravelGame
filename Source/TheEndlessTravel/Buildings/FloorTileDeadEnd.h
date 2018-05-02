// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloorTile.h"
#include "FloorTileDeadEnd.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API AFloorTileDeadEnd : public AFloorTile
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WallEndMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* PortalParticleEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UParticleSystem* PortalParticleEffect;


	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


public:

	AFloorTileDeadEnd();
	virtual FTransform GetAttachTransform() override;
};
