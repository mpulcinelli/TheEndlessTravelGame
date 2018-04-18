// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheEndlessTravelGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountDownToStart, float, CountDownToStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountMetersRun, float, MetersRun);


UCLASS(minimalapi)
class ATheEndlessTravelGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnCountDownToStart OnCountDownToStart;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnCountMetersRun OnCountMetersRun;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* SoundForCountDownIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* SoundForRunningPlay;
	

	int32 CountForwardTile;

	UPROPERTY(VisibleAnywhere)
	FTransform NextSpawnPoint;
	
	virtual void BeginPlay() override;

	TSubclassOf<class AFloorTile> FloorTile;
	
	TSubclassOf<class AFloorTileRamp> FloorTileRamp;

	TSubclassOf<class AFloorTileRampDown> FloorTileRampDown;

	TSubclassOf<class AFloorTileTurnRight> FloorTileTurnRight;

	TSubclassOf<class AFloorTileTurnLeft> FloorTileTurnLeft;

	TSubclassOf<class USoundBase> SoundBaseForCountDownIn;

	class ATheEndlessTravelCharacter* MyCharacter;

	FTimerHandle TimerHandle_StartPlaying;
	FTimerHandle TimerHandle_CountMetersRun;

	float CoinCollected;

	float MetersIncremented;

public:
	ATheEndlessTravelGameMode();

	int32 CountDownToStart;
	
	void AddFloorTile();

	void SpawnTurnRightTile();

	void SpawnTurnLeftTile();

	void SpawnRampDownTile();

	void SpawnRampUpTile();

	void SpawnForwardTile();

	void StartPlayerRunning();

	void CountPlayerCoin(float coinValue);

	float GetTotalCoinCollectedByPlayer();

	void RestartDeadPlayers();

	void PlayAudioForCountDown();

	void PlayAudioForRunningPlay();

	void CountMetersRun();
};



