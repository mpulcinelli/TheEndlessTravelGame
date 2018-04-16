// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpBattery.h"


// Sets default values
APowerUpBattery::APowerUpBattery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUpBattery::BeginPlay()
{
	Super::BeginPlay();
	
}

FRotator APowerUpBattery::GetArrowRotation()
{
	return FRotator(1, 1, 1);
}

// Called every frame
void APowerUpBattery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

