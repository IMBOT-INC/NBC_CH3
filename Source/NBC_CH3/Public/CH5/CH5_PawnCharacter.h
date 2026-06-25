// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CH4/PawnCharacter.h"
#include "CH5_PawnCharacter.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class NBC_CH3_API ACH5_PawnCharacter : public APawnCharacter
{
	GENERATED_BODY()

	// UMG 위젯 클래스를 에디터에서 할당받을 변수
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> HUDWidgetClass;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		TObjectPtr<UUserWidget> HUDWidget;
};
