// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/UI/PlayerHUDWidget.h"

#include "CH4/PawnCharacter.h"
#include "CH5/CH5_GameState.h"
#include "Components/TextBlock.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* OwningPawn = GetOwningPlayerPawn();
	APawnCharacter* PawnCharacter = Cast<APawnCharacter>(OwningPawn);


	UWorld* World = GetWorld();
	if (!World){
		return;
	}

	ACH5_GameState* GameState = World->GetGameState<ACH5_GameState>();
	//
	APawnCharacter* PlayerPawn = Cast<APawnCharacter>(OwningPawn);
	if (PawnCharacter){
		PawnCharacter->OnStaminaChange.AddDynamic(
				this,
				&UPlayerHUDWidget::UpdateStamina
				);

		UpdateStamina(PawnCharacter->Stamina);
	}
	if (GameState){
		GameState->OnLevelChange.AddDynamic(this, &UPlayerHUDWidget::UpdateLevel);
		GameState->OnWaveChange.AddDynamic(this, &UPlayerHUDWidget::UpdateWave);
		PlayerPawn->OnStaminaChange.AddDynamic(this, &UPlayerHUDWidget::UpdateStamina);


		UpdateStamina(PlayerPawn->Stamina);
		UpdateLevel(GameState->Level);
		UpdateWave(GameState->Wave);
	}
	GetWorld()->GetTimerManager().SetTimer(
			HUDTimeUpdateTimerHandle,
			this,
			&UPlayerHUDWidget::UpdateTimeFromGameState,
			1.0f,
			true
			);
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
	Time->SetText(FText::FromString(FString::Printf(TEXT("Time: %.0f"), RemainingTime)));
}

void UPlayerHUDWidget::UpdateStamina(float NewStamina)
{
	if (Stamina){
		UE_LOG(LogTemp, Warning, TEXT("PlayerHudWidget: Stamina %0f"), NewStamina);
		Stamina->SetText(FText::FromString(FString::Printf(TEXT("Stamina: %.0f"), NewStamina)));
	}
}

void UPlayerHUDWidget::UpdateLevel(int32 NewLevel)
{
	if (Level){
		Level->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), NewLevel)));
	}
}

void UPlayerHUDWidget::UpdateWave(int32 NewWave)
{
	if (Wave){
		Wave->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d"), NewWave)));
	}
}

void UPlayerHUDWidget::UpdateTime(float NewTime)
{
	if (Time){
		Time->SetText(FText::FromString(FString::Printf(TEXT("Time: %.0f"), NewTime)));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("PlayerHudWidget : NoWidget Time"));
	}
}
