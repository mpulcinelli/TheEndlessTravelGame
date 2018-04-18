// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheEndlessTravelGameMode.h"
#include "TheEndlessTravelCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "FloorTileRamp.h"
#include "FloorTileRampDown.h"
#include "FloorTileTurnRight.h"
#include "FloorTileTurnLeft.h"
#include <TimerManager.h>
#include <Kismet/GameplayStatics.h>
#include "GameHelpers/GameMacros.h"

ATheEndlessTravelGameMode::ATheEndlessTravelGameMode()
{
	CountForwardTile = 0;
	CountDownToStart = 5;
	CoinCollected = 0.0f;
	MetersIncremented = 0.0f;

	static ConstructorHelpers::FClassFinder<AFloorTile> BP_FloorTile(TEXT("/Game/Blueprints/BP_FloorTile"));
	if (BP_FloorTile.Class != nullptr)
	{
		FloorTile = BP_FloorTile.Class;
	}

	static ConstructorHelpers::FClassFinder<AFloorTileRamp> BP_FloorTileRamp(TEXT("/Game/Blueprints/BP_FloorTileRamp"));
	if (BP_FloorTileRamp.Class != nullptr)
	{
		FloorTileRamp = BP_FloorTileRamp.Class;
	}

	static ConstructorHelpers::FClassFinder<AFloorTileRampDown> BP_FloorTileRampDown(TEXT("/Game/Blueprints/BP_FloorTileRampDown"));
	if (BP_FloorTileRampDown.Class != nullptr)
	{
		FloorTileRampDown = BP_FloorTileRampDown.Class;
	}

	static ConstructorHelpers::FClassFinder<AFloorTileTurnRight> BP_FloorTileTurnRight(TEXT("/Game/Blueprints/BP_FloorTileTurnRight"));
	if (BP_FloorTileTurnRight.Class != nullptr)
	{
		FloorTileTurnRight = BP_FloorTileTurnRight.Class;
	}

	static ConstructorHelpers::FClassFinder<AFloorTileTurnLeft> BP_FloorTileTurnLeft(TEXT("/Game/Blueprints/BP_FloorTileTurnLeft"));
	if (BP_FloorTileTurnLeft.Class != nullptr)
	{
		FloorTileTurnLeft = BP_FloorTileTurnLeft.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> Cue_SoundBaseForCountDownIn(TEXT("/Game/Audio/count_down_Cue"));
	if (Cue_SoundBaseForCountDownIn.Object != nullptr)
	{
		SoundForCountDownIn = Cue_SoundBaseForCountDownIn.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> Cue_SoundBaseForRunningPlay(TEXT("/Game/Audio/trance-loop_Cue"));
	if (Cue_SoundBaseForRunningPlay.Object != nullptr)
	{
		SoundForRunningPlay = Cue_SoundBaseForRunningPlay.Object;
	}



	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/RunnerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		
	}
	else
	{
		PRINT_LOG("ERRO:::: ConstructorHelpers::FClassFinder<APawn>");
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_PlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}


}

void ATheEndlessTravelGameMode::AddFloorTile()
{
	int TurnMeTo = FMath::RandRange(1, 4);

	if (CountForwardTile <= 5) {
		this->SpawnForwardTile();
	}
	else{

		if (TurnMeTo == 1){
			this->SpawnTurnRightTile();
		}
		else if (TurnMeTo == 2){
			this->SpawnTurnLeftTile();
		}
		else if (TurnMeTo == 3) {
			this->SpawnRampUpTile();
		}
		else if (TurnMeTo == 4) {
			this->SpawnRampDownTile();
		}
		CountForwardTile = 0;
	}

	CountForwardTile++;
}

void ATheEndlessTravelGameMode::SpawnTurnRightTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTileRampDown != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFloorTileTurnRight* SpawnedFloorTileTurnRight = GameWorld->SpawnActor<AFloorTileTurnRight>((UClass*)FloorTileTurnRight, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTileTurnRight != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTileTurnRight->GetAttachTransform();
			}
		}
	}
}

void ATheEndlessTravelGameMode::SpawnTurnLeftTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTileTurnLeft != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFloorTileTurnLeft* SpawnedFloorTileTurnLeft = GameWorld->SpawnActor<AFloorTileTurnLeft>((UClass*)FloorTileTurnLeft, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTileTurnLeft != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTileTurnLeft->GetAttachTransform();
			}
		}
	}

}

void ATheEndlessTravelGameMode::SpawnRampDownTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTileRampDown != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFloorTileRampDown* SpawnedFloorTileRampDown = GameWorld->SpawnActor<AFloorTileRampDown>((UClass*)FloorTileRampDown, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTileRampDown != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTileRampDown->GetAttachTransform();
			}
		}
	}
}

void ATheEndlessTravelGameMode::SpawnRampUpTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTileRamp != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFloorTileRamp* SpawnedFloorTileRamp = GameWorld->SpawnActor<AFloorTileRamp>((UClass*)FloorTileRamp, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTileRamp != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTileRamp->GetAttachTransform();
			}
		}
	}
}

void ATheEndlessTravelGameMode::SpawnForwardTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTile != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AFloorTile* SpawnedFloorTile = GameWorld->SpawnActor<AFloorTile>((UClass*)FloorTile, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTile != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTile->GetAttachTransform();
			}
		}
	}
}



void ATheEndlessTravelGameMode::StartPlayerRunning()
{
	if (CountDownToStart <= 0) {
		
		if (MyCharacter != nullptr)
		{
			MyCharacter->StartRunning();
		}

		GetWorldTimerManager().ClearTimer(TimerHandle_StartPlaying);

		GetWorldTimerManager().SetTimer(TimerHandle_CountMetersRun, this, &ATheEndlessTravelGameMode::CountMetersRun, 0.1, true);
	}

	OnCountDownToStart.Broadcast(CountDownToStart);

	CountDownToStart--;
}

void ATheEndlessTravelGameMode::CountPlayerCoin(float coinValue)
{
	this->CoinCollected += coinValue;
}

float ATheEndlessTravelGameMode::GetTotalCoinCollectedByPlayer()
{
	return this->CoinCollected;
}

void ATheEndlessTravelGameMode::RestartDeadPlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/Map_01");
		}
	}
}




void ATheEndlessTravelGameMode::PlayAudioForCountDown()
{
	UGameplayStatics::PlaySound2D(GetWorld(), SoundForCountDownIn);
	PRINT_LOG("ATheEndlessTravelGameMode::PlayAudioForCountDown");
}

void ATheEndlessTravelGameMode::PlayAudioForRunningPlay()
{
	UGameplayStatics::PlaySound2D(GetWorld(), SoundForRunningPlay);
	PRINT_LOG("ATheEndlessTravelGameMode::PlayAudioForRunningPlay");
}

void ATheEndlessTravelGameMode::CountMetersRun()
{
	if (!MyCharacter->IsDead) {
		MetersIncremented++;
		OnCountMetersRun.Broadcast(MetersIncremented);
	}
}

void ATheEndlessTravelGameMode::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<ATheEndlessTravelCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(TimerHandle_StartPlaying, this, &ATheEndlessTravelGameMode::StartPlayerRunning, 1, true);
	for (int i =0 ;i<10;i++)
	{
		this->AddFloorTile();
	}
}

