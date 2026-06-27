// Fill out your copyright notice in the Description page of Project Settings.


#include "CH5/DeadLine.h"

#include "CH5/CH5_MyGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

class ACH5_MyGameMode;
// Sets default values
ADeadLine::ADeadLine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Root);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADeadLine::Overlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADeadLine::OnEndOverlap);
}


void ADeadLine::Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep,
                        const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap:Start"))
	FVector Point = SweepResult.ImpactPoint;
	if (OtherActor && OtherActor->ActorHasTag("Player")){
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
		                                 FString::Printf(TEXT("Overlap!!!")));
		UE_LOG(LogTemp, Warning, TEXT(" Overlap:OnDestroy"))
		OnDestroy(Point);
		UE_LOG(LogTemp, Warning, TEXT(" Overlap:Destroy"))
		OtherActor->Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT(" Overlap:No "))
}

void ADeadLine::OnEndOverlap(UPrimitiveComponent* OverlappedComp,
                             AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ADeadLine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADeadLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
