// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuSystemGameMode.generated.h"

UCLASS(minimalapi)
class AMenuSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TSubclassOf<class APowerUpBattery> BatteryType;



public:
	AMenuSystemGameMode();
};



