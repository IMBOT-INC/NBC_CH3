// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/CH5_GameInstance.h"

#include "Kismet/GameplayStatics.h"


void UCH5_GameInstance::StartGame(UObject* WorldContextObject)
{
	OpenLevelByIndex(WorldContextObject, 0);
}

void UCH5_GameInstance::RestartCurrentLevel(UObject* WorldContextObject)
{
	OpenLevelByIndex(WorldContextObject, CurrentLevelIndex);
}

void UCH5_GameInstance::OpenMainMenu(UObject* WorldContextObject)
{
	UGameplayStatics::OpenLevel(WorldContextObject, MainMenuLevelName);
}

void UCH5_GameInstance::QuitGame(UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	UKismetSystemLibrary::QuitGame(WorldContextObject, PC, EQuitPreference::Quit, false);
}

void UCH5_GameInstance::OpenLevelByIndex(UObject* WorldContextObject, int32 Index)
{
	if (!WorldContextObject){
		return;
	}

	if (!LevelMaps.IsValidIndex(Index)){
		UE_LOG(LogTemp, Warning, TEXT("LevelMaps[%d] is invalid."), Index);
		return;
	}

	const TSoftObjectPtr<UWorld> OpenMap = LevelMaps[Index];
	if (OpenMap.IsNull()){
		UE_LOG(LogTemp, Warning, TEXT("LevelMaps[%d] is null."), Index);
		return;
	}

	CurrentLevelIndex = Index;

	const FName LevelName = FName(*OpenMap.ToSoftObjectPath().GetLongPackageName());
	UGameplayStatics::OpenLevel(WorldContextObject, LevelName);
}

void UCH5_GameInstance::OpenNextLevel(UObject* WorldContextObject)
{
	OpenLevelByIndex(WorldContextObject, CurrentLevelIndex + 1);
}
