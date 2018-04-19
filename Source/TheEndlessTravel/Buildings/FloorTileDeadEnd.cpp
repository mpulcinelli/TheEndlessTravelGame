// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileDeadEnd.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include "FloorTile.h"



AFloorTileDeadEnd::AFloorTileDeadEnd()
{
	WallEndMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallEndMeshComponent"));

	if (WallEndMeshComponent != nullptr)
	{
		WallEndMeshComponent->SetupAttachment(RootComponent);
	}
}

void AFloorTileDeadEnd::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTileDeadEnd::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

FTransform AFloorTileDeadEnd::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}