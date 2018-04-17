// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class THEENDLESSTRAVEL_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class TSubclassOf<class AProjectileBase> ProjectileWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* MuzzleParticleEffect;



	FTimerHandle TimerHandle_TimeBetweemShots;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly)
	float RateOfFire;
	
	float TimeBetweenShots;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Fire();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	void StopFire();

};
