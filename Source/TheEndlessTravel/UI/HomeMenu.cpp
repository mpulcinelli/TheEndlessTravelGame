// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeMenu.h"
#include <Kismet/GameplayStatics.h>
#include "TheEndlessTravelGameInstance.h"

bool UHomeMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(IniciarJogoButton != nullptr)) return false;
	IniciarJogoButton->OnClicked.AddDynamic(this, &UHomeMenu::OnJogar);

	if (!ensure(SairJogoButton != nullptr)) return false;
	SairJogoButton->OnClicked.AddDynamic(this, &UHomeMenu::OnSair);


	return true;
}

void UHomeMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHomeMenu::Setup()
{
	this->AddToViewport();

	UWorld* W = GetWorld();

	if (!ensure(W != nullptr)) return;

	APlayerController* PlayerController = W->GetFirstPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	//FInputModeUIOnly InputModeData;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}


void UHomeMenu::OnJogar()
{
	UTheEndlessTravelGameInstance* MyGM = Cast<UTheEndlessTravelGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGM != nullptr)
		MyGM->IniciarFase(1);

}

void UHomeMenu::OnSair()
{
	UTheEndlessTravelGameInstance* MyGM = Cast<UTheEndlessTravelGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGM != nullptr)
		MyGM->Terminar();
}
