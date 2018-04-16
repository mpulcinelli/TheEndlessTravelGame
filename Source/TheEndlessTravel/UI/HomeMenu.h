// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "HomeMenu.generated.h"

/**
 * 
 */
UCLASS()
class THEENDLESSTRAVEL_API UHomeMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(Meta = (BindWidget))
	UButton* IniciarJogoButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* SairJogoButton;

	UFUNCTION()
	void OnJogar();

	UFUNCTION()
	void OnSair();

public:

	UFUNCTION()
	void Setup();
};
