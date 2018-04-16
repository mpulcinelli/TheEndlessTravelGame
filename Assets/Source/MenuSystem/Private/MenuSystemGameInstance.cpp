// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuSystemGameInstance.h"
#include "MenuEntrada.h"
#include <UserWidget.h>
#include <UObjectGlobals.h>




void UMenuSystemGameInstance::ShowMenuHome()
{
	
	UMenuEntrada* MenuEntradaGame = CreateWidget<UMenuEntrada>(GetWorld(), TemplateMenuHome);//LoadClass<UMenuEntrada>(nullptr, TEXT("/Game/MenuGame/WBP_MenuGame"));  //

	if (MenuEntradaGame == nullptr)return;

	UE_LOG(LogTemp, Warning, TEXT("Passei pelo create widget"));

//	APlayerController* PC=GetPrimaryPlayerController();
	
//	if (PC == nullptr) { 
//		UE_LOG(LogTemp, Warning, TEXT("Player Controller Não Encontrado."));
//		return;
//	}
	
	UE_LOG(LogTemp, Warning, TEXT("Passei pelo Player Controller"));

	FInputModeGameAndUI PlayMode;

	//PlayMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//PlayMode.SetHideCursorDuringCapture(true);
	//PC->SetInputMode(PlayMode);

	MenuEntradaGame->AddToViewport(9999);

	UE_LOG(LogTemp, Warning, TEXT("Passei pelo Add to Viewport"));

}
