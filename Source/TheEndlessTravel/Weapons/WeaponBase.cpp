// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include <Engine/World.h>
#include <TimerManager.h>
#include <Components/SkeletalMeshComponent.h>
#include "ProjectileBase.h"
#include <ConstructorHelpers.h>
#include <Particles/ParticleSystemComponent.h>


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	if (!ensure(MeshComp != nullptr)) return;

	static ConstructorHelpers::FClassFinder<AProjectileBase> ProjectileBPClass(TEXT("/Game/Blueprints/BP_RifleProjectile"));
	if (ProjectileBPClass.Class != nullptr)
	{
		ProjectileWeapon = ProjectileBPClass.Class;
	}

	RootComponent = MeshComp;
	
	MuzzleParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleParticleEffect"));
	if (!ensure(MuzzleParticleEffect != nullptr)) return;
	MuzzleParticleEffect->SetupAttachment(RootComponent);
	MuzzleParticleEffect->Activate(false);

	MuzzleSocketName = "MuzzleSocket";

	RateOfFire = 600;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	FVector SocketLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
	FRotator SocketRotation = MeshComp->GetSocketRotation(MuzzleSocketName);

	MuzzleParticleEffect->SetRelativeLocation(SocketLocation);
	MuzzleParticleEffect->SetRelativeRotation(SocketRotation);

	TimeBetweenShots = 60 / RateOfFire;

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire()
{
	FVector SpawnPosition = MeshComp->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = MeshComp->GetSocketRotation(MuzzleSocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MuzzleParticleEffect->Activate(true);
	GetWorld()->SpawnActor<AProjectileBase>(ProjectileWeapon, SpawnPosition, SpawnRotation, SpawnParams);
}

void AWeaponBase::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweemShots, this, &AWeaponBase::Fire, TimeBetweenShots, true, FirstDelay);

}

void AWeaponBase::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweemShots);
}

