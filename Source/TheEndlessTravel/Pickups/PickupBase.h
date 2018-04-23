// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PickupBase.generated.h"

UCLASS()
class THEENDLESSTRAVEL_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* PickUpSceneComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PickUpMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PickUpPointLightComponent;

	UPROPERTY(VisibleAnywhere)
	class URotatingMovementComponent* PickUpRotationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* SoundCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ParticleForPickupEffect;


	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* BasePickup;

	UPROPERTY(EditAnywhere)
	float PickupValue;

	UFUNCTION()
	void OnPickUpMeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnDestroyedMe(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetPickupValue();
	
};
