// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/CH5_MyGameMode.h"

#include "Blueprint/UserWidget.h"
#include "CH5/CH5_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void ACH5_MyGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController()){
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(this, false);
	}
}

ACH5_MyGameMode::ACH5_MyGameMode()
{
}

void ACH5_MyGameMode::ShowGameOverWidget()
{
	if (GameOverWidgetClass == nullptr){
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC == nullptr){
		return;
	}

	if (GameOverWidget == nullptr){
		GameOverWidget = CreateWidget<UUserWidget>(PC, GameOverWidgetClass);
	}

	if (GameOverWidget && !GameOverWidget->IsInViewport()){
		GameOverWidget->AddToViewport();
	}

	PC->bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(InputMode);

	UGameplayStatics::SetGamePaused(this, true);
}
