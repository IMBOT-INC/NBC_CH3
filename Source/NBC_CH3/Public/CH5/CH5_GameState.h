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

	int32 LimitWave = 3;
	int32 LimitCheckPoint = 3;
	int32 Wave = 1;
	int32 Level = 1;

	float GetRemainingLevelTime() const;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		TArray<FName> LevelMapNames;
	FTimerHandle WaveTimerHandle;


	void CheckPoint();

	virtual void BeginPlay() override;

protected:
	void Timer();
	void OnLevelTimeUp();
	void NextLevel();
	void NextWave();
};
