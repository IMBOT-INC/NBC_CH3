// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "CH5_MVVMViewModel.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NBC_CH3_API UCH5_PlayerHUDViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void SetStamina(float NewStamina);
	void SetWave(int32 NewWave);
	void SetLevel(int32 NewLevelIndex);
	void SetRemainingTime(float NewTime);
	void SetMaxStamina(float NewMaxStamina);

	UFUNCTION(BlueprintPure, FieldNotify)
		float GetStaminaPercent() const;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
		FText StaminaText;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
		FText WaveText;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
		FText LevelText;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
		FText TimeText;

private:
	UPROPERTY()
		float Stamina = 100.0f;

	UPROPERTY()
		float MaxStamina = 100.0f;
};
