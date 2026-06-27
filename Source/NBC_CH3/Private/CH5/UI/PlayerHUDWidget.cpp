// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/UI/PlayerHUDWidget.h"

#include "CH5/CH5_GameInstance.h"
#include "CH5/CH5_GameState.h"
#include "CH5/CH5_PawnCharacter.h"
#include "CH5/UI/ViewModels/CH5_MVVMViewModel.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* OwningPawn = GetOwningPlayerPawn();
	ACH5_PawnCharacter* PawnCharacter = Cast<ACH5_PawnCharacter>(OwningPawn);

	ViewModel = NewObject<UCH5_PlayerHUDViewModel>(this);

	UWorld* World = GetWorld();
	if (!World){
		return;
	}

	ACH5_GameState* GameState = World->GetGameState<ACH5_GameState>();
	if (PawnCharacter){
		ViewModel->SetMaxStamina(PawnCharacter->GetStaminaMax());

		PawnCharacter->OnStaminaChange.AddDynamic(
				this,
				&UPlayerHUDWidget::UpdateStamina
				);

		UpdateStamina(PawnCharacter->Stamina);
	}
	if (GameState){
		GameState->OnWaveChange.AddDynamic(this, &UPlayerHUDWidget::UpdateWave);
		UpdateWave(GameState->Wave);
	}

	if (UCH5_GameInstance* GameInstance = GetGameInstance<UCH5_GameInstance>()){
		UpdateLevel(GameInstance->CurrentLevelIndex);
	}

	GetWorld()->GetTimerManager().SetTimer(
			HUDTimeUpdateTimerHandle,
			this,
			&UPlayerHUDWidget::UpdateTimeFromGameState,
			1.0f,
			true
			);
}

void UPlayerHUDWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld()){
		World->GetTimerManager().ClearTimer(HUDTimeUpdateTimerHandle);
	}

	if (ACH5_PawnCharacter* PawnCharacter = Cast<ACH5_PawnCharacter>(GetOwningPlayerPawn())){
		PawnCharacter->OnStaminaChange.RemoveDynamic(
				this,
				&UPlayerHUDWidget::UpdateStamina
				);
	}

	if (UWorld* World = GetWorld()){
		if (ACH5_GameState* GameState = World->GetGameState<ACH5_GameState>()){
			GameState->OnWaveChange.RemoveDynamic(
					this,
					&UPlayerHUDWidget::UpdateWave
					);
		}
	}

	Super::NativeDestruct();
}

void UPlayerHUDWidget::UpdateTimeFromGameState()
{
	UWorld* World = GetWorld();
	if (!World){
		return;
	}
	ACH5_GameState* GameState = World->GetGameState<ACH5_GameState>();
	if (!GameState){
		return;
	}
	const float RemainingTime = GameState->GetRemainingLevelTime();
	UpdateTime(RemainingTime);
}

void UPlayerHUDWidget::UpdateStamina(float NewStamina)
{
	if (ViewModel){
		ViewModel->SetStamina(NewStamina);
	}
}

void UPlayerHUDWidget::UpdateLevel(int32 NewLevelIndex)
{
	if (ViewModel){
		ViewModel->SetLevel(NewLevelIndex);
	}
}

void UPlayerHUDWidget::UpdateWave(int32 NewWave)
{
	if (ViewModel){
		ViewModel->SetWave(NewWave);
	}
}

void UPlayerHUDWidget::UpdateTime(float NewTime)
{
	if (ViewModel){
		ViewModel->SetRemainingTime(NewTime);
	}
}
