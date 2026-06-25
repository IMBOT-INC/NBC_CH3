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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStamina, float, NewStamina);

UCLASS()
class NBC_CH3_API APawnCharacter : public APawn
{
	GENERATED_BODY()

public:
	FOnChangeStamina OnStaminaChange;

	// Sets default values for this pawn's properties
	APawnCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
			class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float Stamina = 100.0f;

protected:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> IA_MOVE;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> IA_LOOK;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> IA_RUN;

	UPROPERTY(EditAnywhere)
		bool IsGround = true;


	UFUNCTION()
		void Move(const FInputActionValue& value);
	UFUNCTION()
		void RunStart(const FInputActionValue& value);
	UFUNCTION()
		void RunEnd(const FInputActionValue& value);
	UFUNCTION()
		void Look(const FInputActionValue& value);
	UFUNCTION()
		bool GroundCheck();


	UPROPERTY(EditAnywhere)
		float RunMultiplier = 2.0f;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;
	UPROPERTY(EditAnywhere)
		float MovementSpeedOriginal = 100.f;

	UPROPERTY(EditAnywhere)
		float StaminaDecrease = 10.f;
	UPROPERTY(EditAnywhere)
		float StaminaIncrease = 20.f;


	UPROPERTY(EditAnywhere)
		float StaminaMax = 100.0f;


	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UCameraComponent> CameraComponent;


	virtual void Tick(float DeltaTime) override;

	void SetFalling();
	void UpdateGroundCheck();
	void UpdateRun(float DeltaTime);
	void StaminaCalcWithApply(float DeltaTime, bool type);

	UPROPERTY(VisibleAnywhere)
		bool IsRun = false;
};
