// Fill out your copyright notice in the Description page of Project Settings.


#include "CH3/ActorBase.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AActorBase::AActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>("Root");
	SetRootComponent(Root);
	Root->SetBoxExtent(FVector(200, 200, 50));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh->SetupAttachment(RootComponent);

	Root->SetCollisionObjectType(ECC_WorldDynamic);
	Root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Root->SetCollisionResponseToAllChannels(ECR_Ignore);
	Root->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Root->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
}

void AActorBase::DestroyPlatform()
{
	OnDestroyEffect();
	Destroy();
}
