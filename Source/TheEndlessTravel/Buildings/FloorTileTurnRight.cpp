// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTile.h"
#include "FloorTileTurnRight.h"
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include "TheEndlessTravelCharacter.h"
#include "Components/DecalComponent.h"

AFloorTileTurnRight::AFloorTileTurnRight()
{
	BoxEnableCanTurn = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxEnableCanTurn"));
	ArrowDirecao = CreateDefaultSubobject<UDecalComponent>(TEXT("ArrowDirecao"));
	if(BoxEnableCanTurn!=nullptr)
		BoxEnableCanTurn->SetupAttachment(RootComponent);

	if(ArrowDirecao!=nullptr)
		ArrowDirecao->SetupAttachment(RootComponent);
}

void AFloorTileTurnRight::BeginPlay()
{
	Super::BeginPlay();

	if (BoxEnableCanTurn != nullptr)
	{
		BoxEnableCanTurn->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxEnableCanTurn->SetCollisionResponseToAllChannels(ECR_Ignore);
		BoxEnableCanTurn->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		BoxEnableCanTurn->OnComponentBeginOverlap.AddDynamic(this, &AFloorTileTurnRight::OnBoxEnableCanTurnBeginOverlap);
	}
}

void AFloorTileTurnRight::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

FTransform AFloorTileTurnRight::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

void AFloorTileTurnRight::OnBoxEnableCanTurnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBoxEnableCanTurnBeginOverlap"));

	ATheEndlessTravelCharacter* MyPlayer = Cast<ATheEndlessTravelCharacter>(OtherActor);

	if (MyPlayer != nullptr)
	{
		MyPlayer->CanTurn = true;
	}
}
