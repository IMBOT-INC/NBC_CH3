#include "CH3/Component/Moving.h"

// Sets default values for this component's properties
UMoving::UMoving()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoving::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	StartLocation = Owner->GetActorLocation();
}


// Called every frame
void UMoving::TickComponent(float DeltaTime, ELevelTick TickType,
                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Owner)
	{
		return;
	}

	const FVector NormalizedDirection = MoveDirection.GetSafeNormal();

	FVector NewLocation = Owner->GetActorLocation() + NormalizedDirection *
			MoveSpeed * DeltaTime;
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
