// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheEndlessTravelPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API ATheEndlessTravelPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
		
	ATheEndlessTravelPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTouchInterface* GameTouchInterface;

protected:
	virtual void BeginPlay() override;
};
