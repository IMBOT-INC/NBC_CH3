// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CH5_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API UCH5_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		int32 CurrentLevelIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		TArray<TSoftObjectPtr<UWorld>> LevelMaps;


	UFUNCTION(BlueprintCallable, Category = "Level")
		void OpenLevelByIndex(UObject* WorldContextObject, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void OpenNextLevel(UObject* WorldContextObject);
};
