// Fill out your copyright notice in the Description page of Project Settings.

#include "TheEndlessTravelPlayerController.h"
#include <ConstructorHelpers.h>
#include "GameHelpers/GameMacros.h"




ATheEndlessTravelPlayerController::ATheEndlessTravelPlayerController()
{

}

void ATheEndlessTravelPlayerController::BeginPlay()
{
	PRINT_LOG("ATheEndlessTravelPlayerController::BeginPlay");

	if (GameTouchInterface != nullptr)
	{
		CurrentTouchInterface = GameTouchInterface;
		this->ActivateTouchInterface(GameTouchInterface);
	}

}
