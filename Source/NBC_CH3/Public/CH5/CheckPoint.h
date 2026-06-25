// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

class UBoxComponent;

UCLASS()
class NBC_CH3_API ACheckPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnOverlap(
				UPrimitiveComponent* OverlappedComp,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex,
				bool bFromSweep,
				const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> Root;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> Collision;
};
