// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;

UCLASS()
class NBC_CH3_API APawnCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnCharacter();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
			class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_MOVE;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_LOOK;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 100.0f;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
};
