#include "CH3/Component/MovingComponent.h"

// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	StartLocation = Owner->GetActorLocation();
}


void UMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Owner){
		return;
	}
	const FVector NormalizedDirection = MoveDirection.GetSafeNormal();

	FHitResult Hit;
	FVector NewLocation = Owner->GetActorLocation() + NormalizedDirection *
			MoveSpeed * DeltaTime;
	FVector TestDeltaLocation = NormalizedDirection * MoveSpeed * DeltaTime;


	Owner->SetActorLocation(NewLocation, true, &Hit);
	if (Hit.GetActor() != nullptr){
		const FString HitName = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Error, TEXT("MOVING_COMPONENT: Hit  %s"), *HitName);

		if (Hit.GetActor()->ActorHasTag("Player")){
			APawn* HitPawn = Cast<APawn>(Hit.GetActor());
			if (HitPawn){
				HitPawn->AddActorWorldOffset(TestDeltaLocation, true);
				UE_LOG(LogTemp, Error, TEXT("MOVING_COMPONENT:Hit Player  Location %s"),
				       *HitPawn->GetActorLocation().ToCompactString());

				UE_LOG(LogTemp, Error, TEXT("MOVING_COMPONENT: Hit Player"));
			}
		}
	}

	const float DistanceFromStart = FVector::Dist(StartLocation, NewLocation);
	if (DistanceFromStart >= MaxRange){
		NewLocation = StartLocation + NormalizedDirection * MaxRange;
		Owner->SetActorLocation(NewLocation, true, &Hit);
		MoveDirection *= -1.0f;
	}
}
