#include "CH5/CH5_GameState.h"


float ACH5_GameState::GetRemainingLevelTime() const
{
	if (!GetWorld()){
		return 0.f;
	}
	return GetWorld()->GetTimerManager().GetTimerRemaining(WaveTimerHandle);
}

void ACH5_GameState::BeginPlay()
{
	Super::BeginPlay();
	Timer();
}


void ACH5_GameState::NextWave()
{
	if (Wave >= LimitWave){
		Wave = 1;
		NextLevel();
	}
	else{
		Wave++;
	}
	OnWaveChange.Broadcast(Wave);
}

void ACH5_GameState::CheckPoint()
{
	Timer();
	NextWave();
}


void ACH5_GameState::Timer()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&ACH5_GameState::OnLevelTimeUp,
			30.0f,
			false
			);
}


void ACH5_GameState::OnLevelTimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
	NextWave();
}


void ACH5_GameState::NextLevel()
{
	// 레벨 
	// if (Level > LevelMapNames.Num()){
	// 	return;
	// }
	// Level++;
	// OnLevelChange.Broadcast(Level);
}
