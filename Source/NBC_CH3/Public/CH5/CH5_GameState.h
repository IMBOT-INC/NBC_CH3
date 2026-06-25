// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CH5_GameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveChange, int32, NewWaveValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChange, int32, NewLevelValue);

// DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeChange, float, NewTimeValue);


UCLASS()
class NBC_CH3_API ACH5_GameState : public AGameState
{
	GENERATED_BODY()

public:
	FOnLevelChange OnLevelChange;
	FOnWaveChange OnWaveChange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave")
		int32 LimitWave = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave")
		int32 LimitCheckPoint = 3;

	float GetRemainingLevelTime() const;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Wave = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		TArray<FName> LevelMapNames;
	FTimerHandle WaveTimerHandle;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void NextWave();

protected:
	void CheckPoint();
	void Timer();
	void OnLevelTimeUp();
	void NextLevel();
};
