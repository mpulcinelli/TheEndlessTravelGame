// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HUDControllers.generated.h"



/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API UHUDControllers : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();
	void Setup();
	
protected:

	virtual void NativeConstruct() override;

	class ATheEndlessTravelCharacter* TheEndlessTravelCharacte;

	class ATheEndlessTravelGameMode* TheEndlessTravelGameMode;

	UPROPERTY(Meta = (BindWidget))
	class UButton* JumpButton;

	UPROPERTY(Meta = (BindWidget))
	class UButton* FireButton;


	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CoinColletedText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CountDownToStartText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CountMetersRunText;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetAnimation* AnimationCountDownIn; 

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	UFUNCTION()
	void CountDownTick(float valor);

	UFUNCTION()
	void CountMetersRun(float valor);


	UFUNCTION()
	void OnJumpStart();

	UFUNCTION()
	void OnJumpEnd();

	UFUNCTION()
	void OnFireStart();

	UFUNCTION()
	void OnFireEnd();


};
