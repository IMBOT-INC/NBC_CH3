// Fill out your copyright notice in the Description page of Project Settings.


// - [ ]  `Tick(float DeltaTime)`에서 위치를 변경하여 **왕복 이동** 구현
// - [ ]  `StartLocation`(시작 위치) 저장/기준점으로 사용
// - [ ]  `MoveSpeed`(이동 속도) 적용
// - [ ]  `MaxRange`(왕복 범위) 기준으로 이동 제한

#include "CH3/Component/Moving.h"

// Sets default values for this component's properties
UMoving::UMoving()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoving::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	StartLocation = Owner-> GetActorLocation();
	
}


// Called every frame
void UMoving::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Owner)
	{
		return;
	}
	//
	// Owner->SetActorLocation(StartLocation + MaxRange * DeltaTime);
	//
	const FVector NormalizedDirection = MoveDirection.GetSafeNormal();
	
	FVector NewLocation =Owner->GetActorLocation() + NormalizedDirection * MoveSpeed * DeltaTime;
	Owner->SetActorLocation(NewLocation);
	
	const float DistanceFromStart = FVector::Dist(StartLocation, NewLocation);
	//
	if (DistanceFromStart >= MaxRange)
	{
		NewLocation = StartLocation + NormalizedDirection * MaxRange;
		Owner->SetActorLocation(NewLocation);

		MoveDirection *= -1.0f;
	}
}

