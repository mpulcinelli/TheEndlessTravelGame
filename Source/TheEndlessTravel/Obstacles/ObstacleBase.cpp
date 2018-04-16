// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstacleBase.h"
#include <Components/StaticMeshComponent.h>
#include "TheEndlessTravelCharacter.h"


// Sets default values
AObstacleBase::AObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObstacleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMeshComponent"));
	
	if (ObstacleMeshComponent != nullptr) 
	{
		ObstacleMeshComponent->SetNotifyRigidBodyCollision(true);
		RootComponent = ObstacleMeshComponent;
	}
}

// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ObstacleMeshComponent != nullptr)
	{
		ObstacleMeshComponent->OnComponentHit.AddDynamic(this, &AObstacleBase::OnObstacleMeshHit);
	}

	this->OnDestroyed.AddDynamic(this, &AObstacleBase::OnDestroyedMe);
}


void AObstacleBase::OnDestroyedMe(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT(" AObstacleBase::OnDestroyedMe !!!!"));
}


void AObstacleBase::OnObstacleMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	UE_LOG(LogTemp, Warning, TEXT("BATEU OnObstacleMeshHit"));

	ATheEndlessTravelCharacter* MyPlayer = Cast<ATheEndlessTravelCharacter>(OtherActor);
	
	if (MyPlayer != nullptr && !MyPlayer->IsDead)
	{
		MyPlayer->Death();
	}
}

// Called every frame
void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

