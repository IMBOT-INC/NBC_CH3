// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/CheckPoint.h"

#include "CH5/CH5_GameState.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Root);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlap);
	Collision->SetHiddenInGame(false, true);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
}


void ACheckPoint::OnOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->ActorHasTag(TEXT("Player"))){
		return;
	}

	ACH5_GameState* GameState = GetWorld()->GetGameState<ACH5_GameState>();
	if (!GameState){
		return;
	}

	GameState->CheckPoint();
	Destroy();
}
