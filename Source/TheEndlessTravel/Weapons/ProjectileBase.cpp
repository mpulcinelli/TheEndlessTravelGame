// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	if (!ensure(SphereCollision != nullptr)) return;

	RootComponent = SphereCollision;

	MeshProjectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProjectile"));
	if (!ensure(MeshProjectile != nullptr)) return;
	
	MeshProjectile->SetupAttachment(RootComponent);

	MuzzleParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleParticleEffect"));
	if (!ensure(MeshProjectile != nullptr)) return;
	MuzzleParticleEffect->SetupAttachment(RootComponent);

	ProjectileMoviment = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoviment"));
	if (!ensure(ProjectileMoviment != nullptr)) return;
	
	ProjectileMoviment->UpdatedComponent = RootComponent;
	ProjectileMoviment->InitialSpeed =5000.0f;
	ProjectileMoviment->MaxSpeed = 5000.0f;
	ProjectileMoviment->bRotationFollowsVelocity = true;
	ProjectileMoviment->bShouldBounce = false;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

