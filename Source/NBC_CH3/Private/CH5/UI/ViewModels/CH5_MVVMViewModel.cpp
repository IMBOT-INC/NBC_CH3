// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/UI/ViewModels/CH5_MVVMViewModel.h"

void UCH5_PlayerHUDViewModel::SetStamina(float NewStamina)
{
	const float ClampedStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);

	if (!FMath::IsNearlyEqual(Stamina, ClampedStamina)){
		Stamina = ClampedStamina;

		UE_MVVM_SET_PROPERTY_VALUE(
				StaminaText,
				FText::FromString(FString::Printf(TEXT("Stamina: %.0f"), Stamina))
				);

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}

void UCH5_PlayerHUDViewModel::SetMaxStamina(float NewMaxStamina)
{
	const float SafeMaxStamina = FMath::Max(NewMaxStamina, 1.0f);

	if (!FMath::IsNearlyEqual(MaxStamina, SafeMaxStamina)){
		MaxStamina = SafeMaxStamina;
		SetStamina(Stamina);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}

float UCH5_PlayerHUDViewModel::GetStaminaPercent() const
{
	return MaxStamina > KINDA_SMALL_NUMBER
		       ? Stamina / MaxStamina
		       : 0.0f;
}

void UCH5_PlayerHUDViewModel::SetWave(int32 NewWave)
{
	const FText NewText = FText::FromString(
			FString::Printf(TEXT("Wave: %d"), NewWave)
			);
	UE_MVVM_SET_PROPERTY_VALUE(WaveText, NewText);
}

void UCH5_PlayerHUDViewModel::SetLevel(int32 NewLevelIndex)
{
	const FText NewText = FText::FromString(
			FString::Printf(TEXT("Level: %d"), NewLevelIndex + 1)
			);
	UE_MVVM_SET_PROPERTY_VALUE(LevelText, NewText);
}

void UCH5_PlayerHUDViewModel::SetRemainingTime(float NewTime)
{
	const FText NewText = FText::FromString(
			FString::Printf(TEXT("Time: %.0f"), NewTime));
	UE_MVVM_SET_PROPERTY_VALUE(TimeText, NewText);
}
