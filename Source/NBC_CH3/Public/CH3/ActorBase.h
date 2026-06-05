
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class NBC_CH3_API AActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorBase();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
