// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileTunnel.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/PointLightComponent.h>


AFloorTileTunnel::AFloorTileTunnel()
{
	CeilingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CeilingMeshComponent"));
	CeilingLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("CeilingLightComponent"));

	if (CeilingMeshComponent != nullptr)
		CeilingMeshComponent->SetupAttachment(RootComponent);

	if (CeilingLightComponent != nullptr)
		CeilingLightComponent->SetupAttachment(RootComponent);

}

FTransform AFloorTileTunnel::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

void AFloorTileTunnel::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTileTunnel::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
