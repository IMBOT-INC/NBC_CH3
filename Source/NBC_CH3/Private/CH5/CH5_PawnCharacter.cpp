// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/CH5_PawnCharacter.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void ACH5_PawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("CH5_PawnCharacter BeginPlay"));

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController){
		PlayerController = GetWorld()->GetFirstPlayerController();
	}

	if (!PlayerController){
		return;
	}

	// HUD 위젯 생성 및 표시
	if (HUDWidgetClass){
		HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
		if (HUDWidget){
			HUDWidget->AddToViewport();
		}
	}
}
