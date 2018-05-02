// Fill out your copyright notice in the Description page of Project Settings.

#include "TheEndlessTravelGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UI/HomeMenu.h"
#include "UI/HUDControllers.h"
#include <Kismet/GameplayStatics.h>



UTheEndlessTravelGameInstance::UTheEndlessTravelGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> WBP_HudControllers(TEXT("/Game/UI/WBP_HudControllers"));

	if (!ensure(WBP_HudControllers.Class != nullptr)) return;
	ClassHudController = WBP_HudControllers.Class;


	ConstructorHelpers::FClassFinder<UUserWidget> WBP_HomeMenu(TEXT("/Game/UI/WBP_HomeMenu"));

	if (!ensure(WBP_HomeMenu.Class != nullptr)) return;

	ClassHomeMenu = WBP_HomeMenu.Class;


}

void UTheEndlessTravelGameInstance::Init()
{
	FaseAtual = 1;
}

void UTheEndlessTravelGameInstance::LoadHUDController()
{
	if (!ensure(ClassHudController != nullptr)) return;

	HUDControllers = CreateWidget<UHUDControllers>(this, ClassHudController);

	if (!ensure(HUDControllers != nullptr)) return;

	HUDControllers->Setup();

}

void UTheEndlessTravelGameInstance::LoadHomeMenu()
{
	if (!ensure(ClassHomeMenu != nullptr)) return;

	HomeMenu = CreateWidget<UHomeMenu>(this, ClassHomeMenu);

	if (!ensure(HomeMenu != nullptr)) return;

	HomeMenu->Setup();
}

int UTheEndlessTravelGameInstance::GetFaseAtual()
{
	return FaseAtual;
}

int UTheEndlessTravelGameInstance::CarregarProximaFase()
{
	int ProxFase = FaseAtual + 1;
	this->IniciarFase(ProxFase);
	return ProxFase;
}

void UTheEndlessTravelGameInstance::IniciarFase(int id)
{

	switch (id)
	{
	case 1:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/Map_01"), TRAVEL_Absolute);
		break;

	case 2:
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/Map_02"), TRAVEL_Absolute);
		break;
	default:
		break;
	}

}

void UTheEndlessTravelGameInstance::Terminar()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
