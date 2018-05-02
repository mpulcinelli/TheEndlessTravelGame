// Fill out your copyright notice in the Description page of Project Settings.
#include "HUDControllers.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TheEndlessTravelCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "TheEndlessTravelGameMode.h"
#include "GameHelpers/GameMacros.h"
#include "TheEndlessTravelGameInstance.h"

bool UHUDControllers::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	TheEndlessTravelCharacte = Cast<ATheEndlessTravelCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(TheEndlessTravelCharacte != nullptr)) return false;

	TheEndlessTravelGameInstance = Cast<UTheEndlessTravelGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	
	if (!ensure(TheEndlessTravelGameInstance != nullptr)) return false;

	if (!ensure(JumpButton != nullptr)) return false; 
	
	JumpButton->OnPressed.AddDynamic(this, &UHUDControllers::OnJumpStart);
	JumpButton->OnReleased.AddDynamic(this, &UHUDControllers::OnJumpEnd);

	if (!ensure(FireButton != nullptr)) return false;

	FireButton->OnPressed.AddDynamic(this, &UHUDControllers::OnFireStart);
	FireButton->OnReleased.AddDynamic(this, &UHUDControllers::OnFireEnd);


	if (!ensure(CoinColletedText != nullptr)) return false;

	TheEndlessTravelGameMode = Cast<ATheEndlessTravelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!ensure(TheEndlessTravelGameMode != nullptr)) return false;

	TheEndlessTravelGameMode->OnCountDownToStart.AddDynamic(this, &UHUDControllers::CountDownTick);
	TheEndlessTravelGameMode->OnCountMetersRun.AddDynamic(this, &UHUDControllers::CountMetersRun);
	 
	return true;
}

void UHUDControllers::Setup()
{
	this->AddToViewport();
	
	UWorld* W = GetWorld();
	
	if (!ensure(W != nullptr)) return;
	
	APlayerController* PlayerController = W->GetFirstPlayerController();
	
	if (!ensure(PlayerController != nullptr)) return;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void UHUDControllers::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHUDControllers::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	float totalCoinCollectedByPlayer = TheEndlessTravelGameMode->GetTotalCoinCollectedByPlayer();
	FString levelObjectiveText = TheEndlessTravelGameMode->GetLevelObjective();
	FString levelObjectiveCompletedText = TheEndlessTravelGameMode->GetLevelObjectiveCompleted();

	CoinColletedText->SetText(FText::AsNumber(totalCoinCollectedByPlayer));

	if(LevelObjectiveText!=nullptr)
		LevelObjectiveText->SetText(FText::AsCultureInvariant (levelObjectiveText));

	if(LevelObjectiveCompletedText!=nullptr)
		LevelObjectiveCompletedText->SetText(FText::AsCultureInvariant(levelObjectiveCompletedText));

	int CurLevel = TheEndlessTravelGameInstance->GetFaseAtual();

	if (CurrentLevelText != nullptr)
		CurrentLevelText->SetText(FText::AsNumber(CurLevel));

}

void UHUDControllers::CountDownTick(float valor)
{
	if (valor == 5) {
		CountDownToStartText->SetVisibility(ESlateVisibility::Visible);
		CountDownToStartText->SetText(FText::AsNumber(valor));

		if (AnimationCountDownIn != nullptr) {
			PlayAnimation(AnimationCountDownIn);
		}
		TheEndlessTravelGameMode->PlayAudioForCountDown();
	}
	else if (valor > 0 && valor<5)
	{
		CountDownToStartText->SetText(FText::AsNumber(valor));
		TheEndlessTravelGameMode->PlayAudioForCountDown();
	}
	else
	{
		CountDownToStartText->SetVisibility(ESlateVisibility::Hidden);
		CountDownToStartText->SetText(FText::AsNumber(0));
		TheEndlessTravelGameMode->PlayAudioForRunningPlay();
	}
}

void UHUDControllers::CountMetersRun(float valor)
{
	CountMetersRunText->SetText(FText::AsNumber(valor));
}

void UHUDControllers::OnJumpStart()
{
	if (!ensure(TheEndlessTravelCharacte != nullptr)) return;

	TheEndlessTravelCharacte->Jump();
	PRINT_LOG("UHUDControllers::OnJumpStart");
}

void UHUDControllers::OnJumpEnd()
{
	if (!ensure(TheEndlessTravelCharacte != nullptr)) return;

	TheEndlessTravelCharacte->StopJumping();
	PRINT_LOG("UHUDControllers::OnJumpStart");
}

void UHUDControllers::OnFireStart()
{
	TheEndlessTravelCharacte->StartFiring();
}

void UHUDControllers::OnFireEnd()
{
	TheEndlessTravelCharacte->StopFiring();
}

