// Fill out your copyright notice in the Description page of Project Settings.


#include "CH4/MyGameMode.h"

#include "CH4/PawnCharacter.h"


AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = APawnCharacter::StaticClass();
}
