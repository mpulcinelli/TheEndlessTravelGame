// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "PickupObjective.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API APickupObjective : public APickupBase
{
	GENERATED_BODY()
public:
	APickupObjective();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <class UStaticMesh*> ObjetoMesh;


};
