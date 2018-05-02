// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileDeadEnd.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include "FloorTile.h"
#include <Particles/ParticleSystemComponent.h>
#include "TheEndlessTravelGameInstance.h"

AFloorTileDeadEnd::AFloorTileDeadEnd()
{
	WallEndMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallEndMeshComponent"));

	PortalParticleEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleEffectComponent"));

	if (!ensure(PortalParticleEffectComponent != nullptr)) return;
	PortalParticleEffectComponent->SetupAttachment(RootComponent);
	PortalParticleEffectComponent->Activate(false);


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

	UTheEndlessTravelGameInstance* TheEndlessGameInstance = Cast<UTheEndlessTravelGameInstance>(GetGameInstance());

	if (TheEndlessGameInstance != nullptr)
		TheEndlessGameInstance->CarregarProximaFase();

}

FTransform AFloorTileDeadEnd::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}