

#include "CH3/Component/RotatorComponent.h"

URotatorComponent::URotatorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction*
                                      ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetOwner()->AddActorLocalRotation(RotationSpeed);
}
