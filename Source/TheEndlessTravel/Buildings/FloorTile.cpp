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
#include "Pickups/PickupObjective.h"
#include <Materials/Material.h>

// Sets default values
AFloorTile::AFloorTile()
{
	bCanSpawnObstacle = true;
	bCanSpawnCoin = true;
	bCanSpawnObjectives = true;

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

	static ConstructorHelpers::FClassFinder<APickupObjective> BP_PickupObjective(TEXT("/Game/Blueprints/BP_PickupObjective"));
	if (BP_PickupObjective.Class != nullptr)
	{
		PickupObjective = BP_PickupObjective.Class;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_FloorMaterial(TEXT("/Game/Materials/Buildings/1/Floor/Plate_Aluminium_MAT"));
	if (MAT_FloorMaterial.Succeeded())
	{
		FloorMaterial = MAT_FloorMaterial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_WallsMaterial(TEXT("/Game/Materials/Buildings/1/Walls/Aluminium_Foil_MAT"));
	if (MAT_WallsMaterial.Succeeded())
	{
		WallsMaterial = MAT_WallsMaterial.Object;
	}


}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	if(FloorMaterial!=nullptr)
		FloorMeshComponent->SetMaterial(0, FloorMaterial);

	if (WallsMaterial != nullptr) {
		WallLeftMeshComponent->SetMaterial(0, WallsMaterial);
		WallRightMeshComponent->SetMaterial(0, WallsMaterial);
	}
		


	if (BoxEndTrigger != nullptr)
	{
		BoxEndTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
		BoxEndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnBoxEndTriggerBeginOverlap);
	}

	PositionForObstacle = GetSpawnPointsForObstacles();
	SpawnPointsForCoins = GetSpawnPointsForPickUp(); 
	SpawnPointsForObjetives = GetSpawnPointsForPickUp();
	
	if (PositionForObstacle.Num() > 0 && bCanSpawnObstacle)
	{
		SpawnObstacle();
	}

	if (SpawnPointsForCoins.Num() > 0 && bCanSpawnCoin)
	{
		 SpawnCoins();
	}

	if (SpawnPointsForObjetives.Num() > 0 && bCanSpawnObjectives)
	{
		SpawnObjetives();
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

void AFloorTile::Destroyed()
{
	Super::Destroyed();

	this->DestroyAllActors();
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
				APickupBase* SpawnedCoin = GameWorld->SpawnActor<APickupBase>((UClass*)PickupCoin, (FTransform)SpawnPointsForCoins[i], SpawnParams);
				
				if (!ensure(SpawnedCoin != nullptr)) return;
				
				SpawnedCoin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

void AFloorTile::SpawnObjetives()
{
	int Item = FMath::RandRange(1, 10);

	if (Item != 5)return;

	if (PickupObjective != nullptr)
	{
		UWorld* const GameWorld = GetWorld();

		if (GameWorld != nullptr)
		{
			
			int ItemPositionToSpawn = FMath::RandRange(0, SpawnPointsForObjetives.Num()-1);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			APickupObjective* SpawnedObjective = GameWorld->SpawnActor<APickupObjective>((UClass*)PickupObjective, (FTransform)SpawnPointsForObjetives[ItemPositionToSpawn], SpawnParams);

			if (!ensure(PickupObjective != nullptr)) return;

			SpawnedObjective->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
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

