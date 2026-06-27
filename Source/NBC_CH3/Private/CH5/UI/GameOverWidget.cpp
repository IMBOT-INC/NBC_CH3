// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/UI/GameOverWidget.h"

#include "CH5/CH5_GameInstance.h"
#include "Components/Button.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (RestartButton){
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartThisLevel);
	}
	if (QuitButton){
		QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnQuit);
	}
}

void UGameOverWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (RestartButton){
		RestartButton->OnClicked.RemoveDynamic(this, &UGameOverWidget::OnRestartThisLevel);
	}
	if (QuitButton){
		QuitButton->OnClicked.RemoveDynamic(this, &UGameOverWidget::OnQuit);
	}
}

void UGameOverWidget::OnRestartThisLevel()
{
	UCH5_GameInstance* GameInstance = GetGameInstance<UCH5_GameInstance>();
	GameInstance->RestartCurrentLevel(this);
}

void UGameOverWidget::OnQuit()
{
	UCH5_GameInstance* GameInstance = GetGameInstance<UCH5_GameInstance>();
	GameInstance->QuitGame(this);
}
