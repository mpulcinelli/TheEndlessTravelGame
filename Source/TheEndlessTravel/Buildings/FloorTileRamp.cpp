// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTileRamp.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include <ConstructorHelpers.h>
#include <Materials/Material.h>


AFloorTileRamp::AFloorTileRamp() 
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

void AFloorTileRamp::BeginPlay()
{
	Super::BeginPlay();
	RampMeshComponent->SetMaterial(0, RampMaterial);
}

void AFloorTileRamp::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


FTransform AFloorTileRamp::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}
