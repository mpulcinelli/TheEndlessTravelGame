// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include <Components/BoxComponent.h>
#include "TheEndlessTravelCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "TheEndlessTravelGameMode.h"
#include <ConstructorHelpers.h>
#include <Engine/World.h>
#include <Box.h>
#include "Pickups/PickupBase.h"
#include <Engine/EngineTypes.h>
#include "GameHelpers/GameMacros.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanSpawnObstacle = true;
	bCanSpawnCoin = true;

	FloorSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FloorSceneComponent"));
	FloorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"));
	WallLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallLeftMeshComponent"));
	WallRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallRightMeshComponent"));
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	BoxEndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxEndTrigger"));
	SpawnPointLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointLeft"));
	SpawnPointCenter = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointCenter"));
	SpawnPointRight = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointRight"));
	SpawnCoinArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnCoinArea"));

	if(FloorSceneComponent!= nullptr)
		RootComponent = FloorSceneComponent;

	if (FloorMeshComponent != nullptr)
		FloorMeshComponent->SetupAttachment(RootComponent);

	if (WallLeftMeshComponent != nullptr)
		WallLeftMeshComponent->SetupAttachment(RootComponent);
	
	if (WallRightMeshComponent != nullptr)
		WallRightMeshComponent->SetupAttachment(RootComponent);
	
	if (AttachPoint != nullptr)
		AttachPoint->SetupAttachment(RootComponent);
	
	if (SpawnPointLeft != nullptr)
		SpawnPointLeft->SetupAttachment(RootComponent);
	
	if (SpawnPointCenter != nullptr)
		SpawnPointCenter->SetupAttachment(RootComponent);
	
	if (SpawnPointRight != nullptr)
		SpawnPointRight->SetupAttachment(RootComponent);
	
	if (BoxEndTrigger != nullptr)
		BoxEndTrigger->SetupAttachment(RootComponent);
	
	if (SpawnCoinArea != nullptr)
		SpawnCoinArea->SetupAttachment(RootComponent);
	
	NumCoinsPerFloor = 1;

	static ConstructorHelpers::FClassFinder<AObstacleBase> BP_ObstacleRock(TEXT("/Game/Blueprints/BP_ObstacleRock"));
	if (BP_ObstacleRock.Class != nullptr)
	{
		ObstacleRock = BP_ObstacleRock.Class;
	}

	static ConstructorHelpers::FClassFinder<APickupBase> BP_PickupCoin(TEXT("/Game/Blueprints/BP_PickupCoin"));
	if (BP_PickupCoin.Class != nullptr)
	{
		PickupCoin = BP_PickupCoin.Class;
	}
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	if (BoxEndTrigger != nullptr)
	{
		BoxEndTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
		BoxEndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnBoxEndTriggerBeginOverlap);
	}

	PositionForObstacle = GetSpawnPointsForObstacles();
	SpawnPointsForPickUp = GetSpawnPointsForPickUp(); 

	
	if (PositionForObstacle.Num() > 0 && bCanSpawnObstacle)
	{
		SpawnObstacle();
	}
	


	if (SpawnPointsForPickUp.Num() > 0 && bCanSpawnCoin)
	{
		 SpawnCoins();
	}
}


void AFloorTile::DestroyAllActors()
{
	TArray<AActor*> ItemsToDestroy;

	this->GetAttachedActors(ItemsToDestroy);

	for (AActor* Actor : ItemsToDestroy)
	{
		PRINT_LOG_2("DESTRUINDO %s", *Actor->GetName());
		Actor->Destroy();
	}
}

void AFloorTile::OnBoxEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATheEndlessTravelCharacter* Player = Cast<ATheEndlessTravelCharacter>(OtherActor);

	if (Player != nullptr)
	{
		UWorld* world = GetWorld();
		
		class AGameModeBase* gameMode = UGameplayStatics::GetGameMode((UObject*)world);

		if (gameMode != nullptr)
		{
			ATheEndlessTravelGameMode* GameModeNow = Cast<ATheEndlessTravelGameMode>(gameMode);

			if (GameModeNow != nullptr)
			{
				GameModeNow->AddFloorTile();
				DestroyAllActors();
				SetLifeSpan(2);
			}
		}
	}
}

void AFloorTile::SpawnObstacle()
{
	int32 ItemRand = FMath::RandRange(0, PositionForObstacle.Num()-1);

	if (ObstacleRock != nullptr)
	{
		UWorld* const GameWorld = GetWorld();

		if (GameWorld != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AObstacleBase* SpawnedObstacleRock = GameWorld->SpawnActor<AObstacleBase>((UClass*)ObstacleRock, PositionForObstacle[ItemRand], SpawnParams);
			
			if (!ensure(SpawnedObstacleRock != nullptr)) return;
			
			SpawnedObstacleRock->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AFloorTile::SpawnCoins()
{
	if (PickupCoin != nullptr)
	{
		UWorld* const GameWorld = GetWorld();

		if (GameWorld != nullptr)
		{
			for (int i =0;i<NumCoinsPerFloor;i++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				APickupBase* SpawnedCoin = GameWorld->SpawnActor<APickupBase>((UClass*)PickupCoin, (FTransform)SpawnPointsForPickUp[i], SpawnParams);
				
				if (!ensure(SpawnedCoin != nullptr)) return;
				
				SpawnedCoin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

FTransform AFloorTile::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

TArray<FTransform> AFloorTile::GetSpawnPointsForObstacles()
{
	TArray<FTransform> ArrayTransf;
	ArrayTransf.Add(SpawnPointLeft->GetComponentTransform());
	ArrayTransf.Add(SpawnPointCenter->GetComponentTransform());
	ArrayTransf.Add(SpawnPointRight->GetComponentTransform());

	return ArrayTransf;
}

TArray<FVector> AFloorTile::GetSpawnPointsForPickUp()
{
	FBox x = FBox::BuildAABB(SpawnCoinArea->GetComponentLocation(), SpawnCoinArea->GetScaledBoxExtent());

	TArray<FVector> Items;

	for (int i =0;i<NumCoinsPerFloor;i++)
	{
		FVector randPointInBox = FMath::RandPointInBox(x);
		Items.Add(randPointInBox);
	}

	return Items;
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

