// Fill out your copyright notice in the Description page of Project Settings.
#include "FloorTile.h"
#include "HomeMenuGameMode.h"
#include <GameFramework/PlayerController.h>
#include <Engine/World.h>
#include <ConstructorHelpers.h>
#include "GameHelpers/GameMacros.h"



AHomeMenuGameMode::AHomeMenuGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_PlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	PRINT_LOG("AHomeMenuGameMode");
} 
