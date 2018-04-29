// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacles/ObstacleBase.h"
#include "FloorTile.generated.h"

UCLASS()
class THEENDLESSTRAVEL_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Static Mesh para o Chão */
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WallLeftMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WallRightMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* SpawnPointLeft;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* SpawnPointCenter;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* SpawnPointRight;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnCoinArea;

	UPROPERTY(EditAnywhere)
	bool bCanSpawnObstacle;

	UPROPERTY(EditAnywhere)
	bool bCanSpawnCoin;


	TSubclassOf<class AObstacleBase> ObstacleRock;

	TSubclassOf<class APickupBase> PickupCoin;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> PositionForObstacle;

	UPROPERTY(EditAnywhere)
	TArray<FVector> SpawnPointsForPickUp;

	

	UPROPERTY(EditAnywhere)
	int NumCoinsPerFloor; 

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxEndTrigger;

	UPROPERTY(EditAnywhere)
	class USceneComponent* FloorSceneComponent;

	void DestroyAllActors();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FTransform GetAttachTransform();

	TArray<FTransform> GetSpawnPointsForObstacles();

	TArray<FVector> GetSpawnPointsForPickUp();

	UFUNCTION()
	virtual void OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void SpawnObstacle();

	UFUNCTION()
	void SpawnCoins();


};
