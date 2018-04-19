// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FloorTile.h"
#include "CoreMinimal.h"

#include "FloorTileTurnRight.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API AFloorTileTurnRight : public AFloorTile
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxEnableCanTurn;

	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* ArrowDirecao;

	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


public:
	AFloorTileTurnRight();

	virtual FTransform GetAttachTransform() override;

	UFUNCTION()
	void OnBoxEnableCanTurnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
