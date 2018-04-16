// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "MenuEntrada.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEM_API UMenuEntrada : public UUserWidget
{
	GENERATED_BODY()
	


public:
	virtual bool Initialize();

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(Meta=(BindWidget))
	UButton* HostButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* JoinButton;

};
