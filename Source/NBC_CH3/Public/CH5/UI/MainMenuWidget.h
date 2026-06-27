// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NBC_CH3_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> QuitButton;

private:
	UFUNCTION()
		void OnStartClicked();

	UFUNCTION()
		void OnQuitClicked();
};
