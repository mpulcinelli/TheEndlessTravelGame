// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileRampDown.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AFloorTileRampDown::AFloorTileRampDown()
{
	RampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RampMeshComponent"));

	if(RampMeshComponent!=nullptr)
		RampMeshComponent->SetupAttachment(RootComponent);
}



void AFloorTileRampDown::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTileRampDown::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


FTransform AFloorTileRampDown::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

