// Fill out your copyright notice in the Description page of Project Settings.


#include "CH4/PawnCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnCharacter::APawnCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(false);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}


// Called to bind functionality to input
void APawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!MappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("No mapping context found"));
	}
	if (!IA_LOOK)
	{
		UE_LOG(LogTemp, Warning, TEXT("No look at IA_LOOK"));
	}
	
	if (!IA_MOVE)
	{
		UE_LOG(LogTemp, Warning, TEXT("No look at IA_MOVE"));
	}
	
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(
					IA_LOOK,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Look
			);
			EnhancedInputComponent->BindAction(
					IA_MOVE,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Move
			);
			
		}
	}

}

void APawnCharacter::Move(const FInputActionValue& value)
{
	
	const FVector2D MoveInput = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Move Input: %s"), *MoveInput.ToString());
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	// const FVector DeltaLocation = FVector(MoveInput.X, MoveInput.Y, 0.f);
	const FVector DeltaLocation = FVector(MoveInput.X, MoveInput.Y, 0.f) * MovementSpeed * DeltaTime;
	AddActorLocalOffset(DeltaLocation,true);

}

void APawnCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float MouseSensitivity = 100.f;

	const float YawValue = LookInput.X * MouseSensitivity * DeltaTime;
	const float PitchValue = LookInput.Y * MouseSensitivity * DeltaTime;

	AddActorLocalRotation(FRotator(0.f, YawValue, 0.f));

	FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();
	SpringArmRotation.Pitch = FMath::Clamp(
			SpringArmRotation.Pitch - PitchValue,
			-80.f,
			80.f
	);
	SpringArmRotation.Roll = 0.f;

	SpringArmComponent->SetRelativeRotation(SpringArmRotation);
}
