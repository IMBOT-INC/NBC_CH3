// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NBC_CH3_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> Stamina;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> Level;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> Wave;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> Time;

private:
	FTimerHandle HUDTimeUpdateTimerHandle;
	void UpdateTimeFromGameState();


	UFUNCTION()
		void UpdateStamina(float NewStamina);
	UFUNCTION()
		void UpdateLevel(int32 NewLevel);
	UFUNCTION()
		void UpdateWave(int32 NewWave);
	UFUNCTION()
		void UpdateTime(float NewTime);

public:
};
