// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Particles/ParticleEmitter.h>
#include "TheEndlessTravelCharacter.generated.h"

UCLASS(config=Game)
class ATheEndlessTravelCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ATheEndlessTravelCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION()
	void Death();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ATheEndlessTravelGameMode* TheEndlessTravelGameMode;

	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponBase> StarterWeaponClass;


	float SpeedForward;

	virtual void Tick(float DeltaSeconds) override;

	FRotator DesiredRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ParticleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* SoundCollision;

	FTimerHandle TimerHandle_RespawnTimer;

	UPROPERTY(EditDefaultsOnly)
	float CooldownDuration;


	UPROPERTY(VisibleDefaultsOnly)
	FName WeaponAttachSocketName;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	void Respawn();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);



	// Vira o player para a esquerda.
	void TurnLeft();

	// Vira o player para a direita.
	void TurnRight();

	void TurnCorner();

	void StartRunning();

	void StopFiring();
	void StartFiring();

	void Jump();
	void StopJumping();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsFiring;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsJumping;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool CanTurn;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsDead;
};