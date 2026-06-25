// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NBC_CH3_API UMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction*
	                           ThisTickFunction) override;
	UFUNCTION()
		void OnWaveChanged(int32 value);

private:
	float BaseMoveSpeed = 0.0f;
	float GetWaveSpeedMultiplier(int value);
	TObjectPtr<AActor> Owner = nullptr;
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category="Moving")
		float MoveSpeed;
	UPROPERTY(EditAnywhere, Category="Moving")
		float MaxRange;
	UPROPERTY(EditAnywhere, Category="Moving")
		FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
};
