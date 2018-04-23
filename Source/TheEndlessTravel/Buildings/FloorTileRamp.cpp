// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTileRamp.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>


AFloorTileRamp::AFloorTileRamp() 
{
	RampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RampMeshComponent"));

	if(RampMeshComponent!=nullptr)
		RampMeshComponent->SetupAttachment(RootComponent);
}

void AFloorTileRamp::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTileRamp::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


FTransform AFloorTileRamp::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}
