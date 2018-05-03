// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheEndlessTravelGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API UTheEndlessTravelGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		UTheEndlessTravelGameInstance(const FObjectInitializer & ObjectInitializer);
		
		class UTheEndlessTravelSaveGame* SaveGameInstance;

		virtual void Init();
		
		UFUNCTION(BlueprintCallable)
		void LoadHUDController();

		UFUNCTION(BlueprintCallable)
		void LoadHomeMenu();

		int GetFaseAtual();

		int CarregarProximaFase();

		void IniciarFase(int id);

		void Terminar();

		bool SavePlayerName(FString PlayerName);

		bool SaveCurrentFase(int Id);

private:
	TSubclassOf<class UUserWidget> ClassHudController;

	class UHUDControllers* HUDControllers;

	TSubclassOf<class UUserWidget> ClassHomeMenu;

	class UHomeMenu* HomeMenu;

	int FaseAtual;

};
