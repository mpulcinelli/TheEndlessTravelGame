// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupObjective.h"
#include <Components/StaticMeshComponent.h>
#include "GameHelpers/GameMacros.h"
#include "TheEndlessTravelGameMode.h"
#include <Kismet/GameplayStatics.h>




APickupObjective::APickupObjective()
{

}

void APickupObjective::BeginPlay()
{
	Super::BeginPlay();
	this->ChooseItemToSpawn();
}

void APickupObjective::OnPickUpMeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPickUpMeshComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	ATheEndlessTravelGameMode* TheEndlessTravelGameMode;

	TheEndlessTravelGameMode = Cast<ATheEndlessTravelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!ensure(TheEndlessTravelGameMode != nullptr)) return;
	
	OtherActor->GetComponentByClass(UStaticMeshComponent::StaticClass());

	
	if (OverlappedComponent->ComponentTags.Num() <= 0)return;

	TheEndlessTravelGameMode->SetObjectiveItem(*OverlappedComponent->ComponentTags[0].ToString());

	//PRINT_LOG_2("Chamando Over OnPickUpMeshComponentBeginOverlap: %s ", *OverlappedComponent->ComponentTags[0].ToString());
}

void APickupObjective::ChooseItemToSpawn()
{
	if (PickupItens.Num() > 0)
	{
		int randRange = FMath::RandRange(0, PickupItens.Num() - 1);
		
		if (PickupItens[randRange].MeshToPresent != nullptr) {
			PickUpMeshComponent->SetStaticMesh(PickupItens[randRange].MeshToPresent);
			PickUpMeshComponent->ComponentTags.Add(FName(*PickupItens[randRange].NomeItem));
		}
	}
}
