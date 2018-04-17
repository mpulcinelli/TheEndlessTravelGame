// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "TheEndlessTravelCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <Sound/SoundBase.h>
#include <GameFramework/Character.h>
#include <TimerManager.h>
#include "Components/SkeletalMeshComponent.h"
#include "Pickups/PickupBase.h"
#include "TheEndlessTravelGameMode.h"
#include "GameHelpers/GameMacros.h"
#include "Weapons/WeaponBase.h"
//////////////////////////////////////////////////////////////////////////
// ATheEndlessTravelCharacter

ATheEndlessTravelCharacter::ATheEndlessTravelCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CanTurn = false;
	IsDead = false;
	CooldownDuration = 3;
	
	WeaponAttachSocketName = "WeaponSocket";

	SpeedForward = 0.0f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 1500;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TheEndlessTravelGameMode = Cast<ATheEndlessTravelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

}

void ATheEndlessTravelCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}

}

void ATheEndlessTravelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsDead)return;

	this->TurnCorner();

	// Executa o movimeto para frente do player.
	this->MoveForward(SpeedForward);
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATheEndlessTravelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATheEndlessTravelCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATheEndlessTravelCharacter::StopJumping);

	PlayerInputComponent->BindAction("TurnLeft", IE_Pressed, this, &ATheEndlessTravelCharacter::TurnLeft);
	PlayerInputComponent->BindAction("TurnRight", IE_Pressed, this, &ATheEndlessTravelCharacter::TurnRight);

	PlayerInputComponent->BindAction("Firing", IE_Pressed, this, &ATheEndlessTravelCharacter::StartFiring);
	PlayerInputComponent->BindAction("Firing", IE_Released, this, &ATheEndlessTravelCharacter::StopFiring);


	PlayerInputComponent->BindAxis("MoveRight", this, &ATheEndlessTravelCharacter::MoveRight);
}

void ATheEndlessTravelCharacter::Respawn()
{
	UWorld* world = GetWorld();
	if (world != nullptr) {

		AGameModeBase* gameMode = UGameplayStatics::GetGameMode((UObject*)world);

		if (gameMode != nullptr) {
			ATheEndlessTravelGameMode* CurrentGameMode = Cast<ATheEndlessTravelGameMode>(gameMode);
			if (CurrentGameMode != nullptr) {
				CurrentGameMode->RestartDeadPlayers();
			}
		}
	}
}

void ATheEndlessTravelCharacter::StartRunning()
{
	SpeedForward = 1.0f;
}

void ATheEndlessTravelCharacter::StopJumping()
{
	this->IsJumping = false;
	PRINT_LOG("StopJumping");
	Super::StopJumping();
}

void ATheEndlessTravelCharacter::Jump()
{
	this->IsJumping = true;
	Super::Jump();
}



void ATheEndlessTravelCharacter::StopFiring()
{
	this->IsFiring = false;
	CurrentWeapon->StopFire();
}

void ATheEndlessTravelCharacter::StartFiring()
{
	this->IsFiring = true;
	if (!IsDead)
	{
		CurrentWeapon->StartFire();
	}
}

void ATheEndlessTravelCharacter::Death()
{
	IsDead = true;

	GetMovementComponent()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetachFromControllerPendingDestroy();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleCollision, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCollision, GetActorLocation());

	this->GetMesh()->SetVisibility(false, true);
	
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ATheEndlessTravelCharacter::Respawn, CooldownDuration);

	this->StopFiring();
}



void ATheEndlessTravelCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APickupBase* Coin = Cast<APickupBase>(OtherActor);

	if (Coin != nullptr) {
		if (TheEndlessTravelGameMode != nullptr) {
			TheEndlessTravelGameMode->CountPlayerCoin(Coin->GetPickupValue());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(Coin->GetPickupValue()));
		}
	}
}

void ATheEndlessTravelCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATheEndlessTravelCharacter::MoveRight(float Value)
{

//	UE_LOG(LogTemp, Warning, TEXT("MoveRight %s"), *FString::SanitizeFloat(Value));

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

		if (Value==-1.0f)
		{
			TurnLeft();
		}else if (Value == 1.0f)
		{
			TurnRight();
		}

	}
}

void ATheEndlessTravelCharacter::TurnLeft()
{
	if (CanTurn)
	{
		FRotator MyRotator;


		MyRotator.Pitch = 0.0f;
		MyRotator.Roll = 0.0f;
		MyRotator.Yaw = -90.0f;

		FQuat AQuat = FQuat(DesiredRotation);
		FQuat BQuat = FQuat(MyRotator);

		DesiredRotation = FRotator(AQuat* BQuat);
		CanTurn = false;
	}

}

void ATheEndlessTravelCharacter::TurnRight()
{
	if (CanTurn)
	{
		FRotator MyRotator;

		MyRotator.Pitch = 0.0f;
		MyRotator.Roll = 0.0f;
		MyRotator.Yaw = 90.0f;

		FQuat AQuat = FQuat(DesiredRotation);
		FQuat BQuat = FQuat(MyRotator);

		DesiredRotation = FRotator(AQuat* BQuat);
		
		CanTurn = false;
	}
}

void ATheEndlessTravelCharacter::TurnCorner()
{
	FRotator MyControlRotation = GetControlRotation();
	APlayerController* MyPC = nullptr;

	if (MyControlRotation != DesiredRotation)
	{
		for (FConstPlayerControllerIterator IPC = GetWorld()->GetPlayerControllerIterator(); IPC; ++IPC)
		{
			MyPC= IPC->Get();
			break; 
		}

		if(MyPC!=nullptr)
		{
			FRotator MyRInterpTo = FMath::RInterpTo(MyControlRotation, DesiredRotation, GetWorld()->GetDeltaSeconds(), 15);

			MyPC->SetControlRotation(MyRInterpTo);
		}
	}
}

