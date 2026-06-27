// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NBC_CH3_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> QuitButton;

private:
	UFUNCTION()
		void OnRestartThisLevel();

	UFUNCTION()
		void OnQuit();
};
