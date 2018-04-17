// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstacleBase.h"
#include <Components/StaticMeshComponent.h>
#include "TheEndlessTravelCharacter.h"
#include <../Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleComponent.h>
#include "Weapons/ProjectileBase.h"



// Sets default values
AObstacleBase::AObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	DestructibleObstacle=CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleObstacle"));

	if (DestructibleObstacle != nullptr)
	{
		DestructibleObstacle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		DestructibleObstacle->SetSimulatePhysics(true);
		DestructibleObstacle->SetEnableGravity(false);
		DestructibleObstacle->WakeRigidBody(NAME_None);

		RootComponent = DestructibleObstacle;
		//DestructibleObstacle->SetupAttachment(RootComponent);
	}

	

}

// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (DestructibleObstacle != nullptr)
	{
		DestructibleObstacle->SetNotifyRigidBodyCollision(true);

		DestructibleObstacle->OnComponentHit.AddDynamic(this, &AObstacleBase::OnObstacleMeshHit);
	}

	this->OnDestroyed.AddDynamic(this, &AObstacleBase::OnDestroyedMe);
}


void AObstacleBase::OnDestroyedMe(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT(" AObstacleBase::OnDestroyedMe !!!!"));
}


void AObstacleBase::ApplyFracture()
{
}

void AObstacleBase::OnObstacleMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	UE_LOG(LogTemp, Warning, TEXT("BATEU OnObstacleMeshHit"));

	ATheEndlessTravelCharacter* MyPlayer = Cast<ATheEndlessTravelCharacter>(OtherActor);
	
	if (MyPlayer != nullptr && !MyPlayer->IsDead)
	{
		MyPlayer->Death();
	}

	AProjectileBase* Projectile = Cast<AProjectileBase>(OtherActor);

	if (Projectile!=nullptr) {
		
		DestructibleObstacle->ApplyRadiusDamage(5000, Hit.Location, 100, 10000, false);
		SetLifeSpan(1);
	}

}

// Called every frame
void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

