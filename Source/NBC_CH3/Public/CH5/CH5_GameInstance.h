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

	UPROPERTY(EditAnywhere)
		int32 CurretLevel = 1;

	UPROPERTY(EditAnywhere)
		TArray<FName> LevelMaps;
};
