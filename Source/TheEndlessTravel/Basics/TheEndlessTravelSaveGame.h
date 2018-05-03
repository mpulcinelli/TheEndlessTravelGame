// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TheEndlessTravelSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API UTheEndlessTravelSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UTheEndlessTravelSaveGame();

	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 UserIndex;

public:
	UPROPERTY(VisibleAnywhere)
	FString PlayerName;
	
	UPROPERTY(VisibleAnywhere)
	int CurrentFase;

};
