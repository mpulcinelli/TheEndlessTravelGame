// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "PickupObjective.generated.h"

USTRUCT(BlueprintType)
struct FItemToPickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NomeItem; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MeshToPresent;
};


UCLASS()
class THEENDLESSTRAVEL_API APickupObjective : public APickupBase
{
	GENERATED_BODY()
public:
	APickupObjective();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemToPickup> PickupItens;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnPickUpMeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

private:

	void ChooseItemToSpawn();

};
