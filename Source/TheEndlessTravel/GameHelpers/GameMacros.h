// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"

// LOG PARA ARQUIVO
#define PRINT_LOG(TEXT_TO_LOG) UE_LOG(LogTemp, Warning, TEXT(TEXT_TO_LOG));
#define PRINT_LOG_2(TEXT_TO_LOG, PARAM) UE_LOG(LogTemp, Warning, TEXT(TEXT_TO_LOG), PARAM);

// LOG PARA TELA
#define PRINT_TO_SCREEN(TEXT_TO_PRINT) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT_TO_PRINT);
