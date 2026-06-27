// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UCH5_PlayerHUDViewModel;
/**
 * 
 */
UCLASS()
class NBC_CH3_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "MVVM", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCH5_PlayerHUDViewModel> ViewModel;

	FTimerHandle HUDTimeUpdateTimerHandle;
	void UpdateTimeFromGameState();


	UFUNCTION()
		void UpdateStamina(float NewStamina);
	UFUNCTION()
		void UpdateLevel(int32 NewLevelIndex);
	UFUNCTION()
		void UpdateWave(int32 NewWave);
	UFUNCTION()
		void UpdateTime(float NewTime);

public:
};
