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
	if (!GameOverWidgetClass){
		UE_LOG(LogTemp, Error, TEXT("GameOverWidgetClass is null"));
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC){
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	if (!GameOverWidget){
		GameOverWidget = CreateWidget<UUserWidget>(PC, GameOverWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("Create GameOverWidget: %s"), *GetNameSafe(GameOverWidget));
	}

	if (!GameOverWidget){
		UE_LOG(LogTemp, Error, TEXT("GameOverWidget create failed"));
		return;
	}

	GameOverWidget->SetVisibility(ESlateVisibility::Visible);

	if (!GameOverWidget->IsInViewport()){
		GameOverWidget->AddToViewport(100);
		UE_LOG(LogTemp, Warning, TEXT("GameOverWidget AddToViewport"));
	}

	PC->bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(InputMode);

	UGameplayStatics::SetGamePaused(this, true);
}