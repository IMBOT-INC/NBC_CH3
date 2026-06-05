// Fill out your copyright notice in the Description page of Project Settings.


#include "CH3/ActorBase.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AActorBase::AActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh ->SetupAttachment(RootComponent);
	
}


