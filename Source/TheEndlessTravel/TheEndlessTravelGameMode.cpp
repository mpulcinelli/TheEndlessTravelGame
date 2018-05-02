// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheEndlessTravelGameMode.h"
#include "TheEndlessTravelCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Buildings/FloorTileRamp.h"
#include "Buildings/FloorTileRampDown.h"
#include "Buildings/FloorTileTurnRight.h"
#include "Buildings/FloorTileTurnLeft.h"
#include <TimerManager.h>
#include <Kismet/GameplayStatics.h>
#include "GameHelpers/GameMacros.h"
#include "Buildings/FloorTileTunnel.h"
#include "TheEndlessTravelGameInstance.h"
#include "Buildings/FloorTileDeadEnd.h"

ATheEndlessTravelGameMode::ATheEndlessTravelGameMode()
{
	CountForwardTile = 0;
	CountDownToStart = 5;
	CoinCollected = 0.0f;
	MetersIncremented = 0.0f;
	LastItemCreated = false;

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

	static ConstructorHelpers::FClassFinder<AFloorTileTunnel> BP_FloorTileTunnel(TEXT("/Game/Blueprints/BP_FloorTileTunnel"));
	if (BP_FloorTileTunnel.Class != nullptr)
	{
		FloorTileTunnel = BP_FloorTileTunnel.Class;
	}

	static ConstructorHelpers::FClassFinder<AFloorTileDeadEnd> BP_FloorTileDeadEnd(TEXT("/Game/Blueprints/BP_FloorTileDeadEnd"));
	if (BP_FloorTileDeadEnd.Class != nullptr)
	{
		FloorTileDeadEnd = BP_FloorTileDeadEnd.Class;
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
	if (LastItemCreated)return;

	if (this->IsObjectiveCompleted())
	{
		LastItemCreated = true;
		this->SpawnDeadEndTile();
	}
	else 
	{
		int BuildingItem = FMath::RandRange(1, 5);

		if (CountForwardTile <= 5) {
			this->SpawnForwardTile();
		}
		else {

			if (BuildingItem == 1) {
				this->SpawnTurnRightTile();
			}
			else if (BuildingItem == 2) {
				this->SpawnTurnLeftTile();
			}
			else if (BuildingItem == 3) {
				this->SpawnRampUpTile();
			}
			else if (BuildingItem == 4) {
				this->SpawnRampDownTile();
			}
			else if (BuildingItem == 5) {
				int TunnelSize = FMath::RandRange(1, 5);

				for (int i = 1; i <= TunnelSize; i++)
				{
					this->SpawnTunnelTile();
				}
			}
			CountForwardTile = 0;
		}

		CountForwardTile++;
	}
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

void ATheEndlessTravelGameMode::SpawnDeadEndTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTileDeadEnd != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AFloorTile* SpawnedFloorTileDeadEnd = GameWorld->SpawnActor<AFloorTile>((UClass*)FloorTileDeadEnd, NextSpawnPoint, SpawnParams);

			if (SpawnedFloorTileDeadEnd != nullptr)
			{
				NextSpawnPoint = SpawnedFloorTileDeadEnd->GetAttachTransform();
			}
		}
	}
}


void ATheEndlessTravelGameMode::SpawnTunnelTile()
{
	UWorld* const GameWorld = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (FloorTile != nullptr)
	{
		if (GameWorld != nullptr)
		{
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AFloorTileTunnel* SpawnedFloorTile = GameWorld->SpawnActor<AFloorTileTunnel>((UClass*)FloorTileTunnel, NextSpawnPoint, SpawnParams);

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
	if (!MyCharacter->IsDead && MyCharacter->IsMoving()) {
		MetersIncremented++;
		OnCountMetersRun.Broadcast(MetersIncremented);
	}
}

FString ATheEndlessTravelGameMode::GetLevelObjective()
{
	switch (CurrentLevel)
	{
	case 1:
		return "RUNNER";

	case 2:
		return "DEATH";
		// TODO: Criar os meshs para todas as letras do alfabeto.
	default:
		return "";
		break;
	}
}

FString ATheEndlessTravelGameMode::GetLevelObjectiveCompleted()
{
	FString ConcatItems;
	for (FString item : CollectedObjeciveItems)
	{
		ConcatItems.Append(item);
	}

	return ConcatItems;
}

void ATheEndlessTravelGameMode::SetObjectiveItem(FString letra)
{
	FString levelObjective = this->GetLevelObjective();

	if (Letters.Num() <= 0) {
		for (int i = 0; i < levelObjective.Len(); i++)
		{
			Letters.Add(levelObjective.Mid(i, 1));
		}
	}

	if (CollectedObjeciveItems.Num() <= 0) {
		for (int i = 0; i<Letters.Num(); i++)
		{
			CollectedObjeciveItems.Add(" ");
		}
	}

	for (int i=0;i<Letters.Num();i++)
	{
		if (letra == Letters[i] && CollectedObjeciveItems[i] == " ")
		{
			CollectedObjeciveItems[i] = letra;
			break;
		}
	}
}

bool ATheEndlessTravelGameMode::IsObjectiveCompleted()
{
	if (Letters.Num() <= 0)return false;

	for (int i = 0; i < Letters.Num(); i++)
	{
		if (Letters[i] != CollectedObjeciveItems[i]) {
			return false;
		}
	}

	return true;
}

void ATheEndlessTravelGameMode::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<ATheEndlessTravelCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	TheEndlessGameInstance = Cast<UTheEndlessTravelGameInstance>(GetGameInstance());

	if (TheEndlessGameInstance != nullptr)
		CurrentLevel = TheEndlessGameInstance->GetFaseAtual();
	else
		CurrentLevel = 1;

	GetWorldTimerManager().SetTimer(TimerHandle_StartPlaying, this, &ATheEndlessTravelGameMode::StartPlayerRunning, 1, true);
	
	for (int i =0 ;i<10;i++)
	{
		this->AddFloorTile();
	}
}

