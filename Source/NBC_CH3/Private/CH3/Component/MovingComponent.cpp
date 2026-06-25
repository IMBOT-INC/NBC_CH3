#include "CH3/Component/MovingComponent.h"

#include "AudioDeviceManager.h"
#include "CH5/CH5_GameState.h"

// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!Owner){
		return;
	}

	StartLocation = Owner->GetActorLocation();
	BaseMoveSpeed = MoveSpeed;
	if (UWorld* World = GetWorld()){
		if (ACH5_GameState* GameState = World->GetGameState<ACH5_GameState>()){
			GameState->OnWaveChange.AddDynamic(this, &UMovingComponent::OnWaveChanged);
			OnWaveChanged(GameState->Wave);
		}
	}
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
	FVector TestDeltaLocation = NormalizedDirection * (MoveSpeed * 2) * DeltaTime;


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

void UMovingComponent::OnWaveChanged(int32 value)
{
	MoveSpeed = BaseMoveSpeed * GetWaveSpeedMultiplier(value);
}

float UMovingComponent::GetWaveSpeedMultiplier(int32 Wave)
{
	switch (Wave){
	case 1:
		return 1.3f;
	case 2:
		return 1.5f;
	case 3:
		return 2.0f;
	default:
		return 2.0f;
	}
}
