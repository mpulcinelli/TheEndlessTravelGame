// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTileTurnLeft.h"
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include "TheEndlessTravelCharacter.h"
#include <Components/DecalComponent.h>
#include "GameHelpers/GameMacros.h"


// Sets default values
AFloorTileTurnLeft::AFloorTileTurnLeft()
{
	BoxEnableCanTurn = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxEnableCanTurn"));
	ArrowDirecao = CreateDefaultSubobject<UDecalComponent>(TEXT("ArrowDirecao"));

	if (BoxEnableCanTurn != nullptr)
		BoxEnableCanTurn->SetupAttachment(RootComponent);

	if (ArrowDirecao != nullptr)
		ArrowDirecao->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AFloorTileTurnLeft::BeginPlay()
{
	Super::BeginPlay();

	if (BoxEnableCanTurn != nullptr)
	{
		BoxEnableCanTurn->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxEnableCanTurn->SetCollisionResponseToAllChannels(ECR_Ignore);
		BoxEnableCanTurn->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		BoxEnableCanTurn->OnComponentBeginOverlap.AddDynamic(this, &AFloorTileTurnLeft::OnBoxEnableCanTurnBeginOverlap);
	}
}


void AFloorTileTurnLeft::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBoxEndTriggerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

FTransform AFloorTileTurnLeft::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

void AFloorTileTurnLeft::OnBoxEnableCanTurnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATheEndlessTravelCharacter* MyPlayer = Cast<ATheEndlessTravelCharacter>(OtherActor);

	if (MyPlayer != nullptr)
	{
		MyPlayer->CanTurn = true;
	}
}
