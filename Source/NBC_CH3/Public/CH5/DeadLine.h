// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadLine.generated.h"

class UBoxComponent;
class USphereComponent;

UCLASS()
class NBC_CH3_API ADeadLine : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeadLine();

private:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> Collision;
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> Root;

protected:
	UFUNCTION()
		void Overlap(
				UPrimitiveComponent* OverlappedComp,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex,
				bool bFromSweep,
				const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnEndOverlap(
				UPrimitiveComponent* OverlappedComp,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDestroy(FVector Location);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called every frame
};
