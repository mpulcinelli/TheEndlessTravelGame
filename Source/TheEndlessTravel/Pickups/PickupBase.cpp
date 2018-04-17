// Fill out your copyright notice in the Description page of Project Settings.
#include "PickupBase.h"
#include "Components/SceneComponent.h"
#include <Components/PointLightComponent.h>
#include <GameFramework/RotatingMovementComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Sound/SoundBase.h>
#include <Kismet/GameplayStatics.h>
#include <Components/DecalComponent.h>

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpSceneComponent"));
	PickUpMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMeshComponent"));
	PickUpPointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PickUpPointLightComponent"));
	PickUpRotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("PickUpRotationComponent"));
	//BasePickup = CreateDefaultSubobject<UDecalComponent>(TEXT("BasePickup"));

	if (PickUpSceneComponent != nullptr)
		RootComponent = PickUpSceneComponent;

	if(PickUpMeshComponent!= nullptr)
		PickUpMeshComponent->SetupAttachment(RootComponent);
	
	if(PickUpPointLightComponent!= nullptr)
		PickUpPointLightComponent->SetupAttachment(RootComponent);
	
	//BasePickup->SetupAttachment(RootComponent);
	if(PickUpRotationComponent!= nullptr)
		PickUpRotationComponent->SetUpdatedComponent(RootComponent);
	
	PickupValue = 10;

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	if(PickUpSceneComponent!= nullptr)
		PickUpSceneComponent->SetMobility(EComponentMobility::Movable);
	
	if (PickUpMeshComponent!= nullptr)
	{
		PickUpMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PickUpMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		PickUpMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		PickUpMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickUpMeshComponentBeginOverlap);
	}

	this->OnDestroyed.AddDynamic(this, &APickupBase::OnDestroyedMe);
}

void APickupBase::OnPickUpMeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (SoundCollision != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCollision, GetActorLocation());
	}
	
	Destroy();
}

void APickupBase::OnDestroyedMe(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT(" APickupBase::OnDestroyedMe !!!!"));
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float APickupBase::GetPickupValue()
{
	return PickupValue;
}

