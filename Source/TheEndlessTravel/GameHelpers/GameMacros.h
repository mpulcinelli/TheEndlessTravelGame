// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define PRINT_LOG(TEXT_TO_LOG) UE_LOG(LogTemp, Warning, TEXT(TEXT_TO_LOG));
#define PRINT_LOG_2(TEXT_TO_LOG, PARAM) UE_LOG(LogTemp, Warning, TEXT(TEXT_TO_LOG), PARAM);