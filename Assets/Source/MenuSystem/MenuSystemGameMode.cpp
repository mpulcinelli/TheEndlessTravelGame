// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MenuSystemGameMode.h"
#include "MenuSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Engine/World.h>
#include "PowerUpBattery.h"


void AMenuSystemGameMode::BeginPlay()
{
	//Blueprint'/Game/BP_MyPowerUpBattery.BP_MyPowerUpBattery'

	if (BatteryType != NULL)
	{
		UWorld* const GameWorld = GetWorld();
		FTransform ObjectTransf;
		FActorSpawnParameters SpawnParameters;
		
		APowerUpBattery* SpawnedItem = GameWorld->SpawnActor<APowerUpBattery>((UClass*)BatteryType, ObjectTransf, SpawnParameters);
		SpawnedItem->GetArrowRotation();
	}
}

AMenuSystemGameMode::AMenuSystemGameMode()
{

	static ConstructorHelpers::FClassFinder<APowerUpBattery> BP_PowerUp(TEXT("/Game/BP_MyPowerUpBattery"));
	if (BP_PowerUp.Class != NULL)
	{
		BatteryType = BP_PowerUp.Class;
	}


	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
