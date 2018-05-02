// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileRampDown.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include <ConstructorHelpers.h>
#include <Materials/Material.h>

// Sets default values
AFloorTileRampDown::AFloorTileRampDown()
{
	RampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RampMeshComponent"));

	if(RampMeshComponent!=nullptr)
		RampMeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_RampMaterial(TEXT("/Game/Materials/Buildings/1/Ramps/Copper_Brushed_MAT"));
	if (MAT_RampMaterial.Succeeded())
	{
		RampMaterial = MAT_RampMaterial.Object;
	}

}



void AFloorTileRampDown::BeginPlay()
{
	Super::BeginPlay();
	RampMeshComponent->SetMaterial(0, RampMaterial);
}

void AFloorTileRampDown::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


FTransform AFloorTileRampDown::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

