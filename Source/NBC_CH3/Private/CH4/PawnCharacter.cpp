#include "CH4/PawnCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnCharacter::APawnCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>
			("CapsuleComponent");
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(
			"SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(
			"SpringArmComponent");
	SpringArmComponent->SetupAttachment(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(
			"CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CapsuleComponent->SetCollisionObjectType(ECC_Pawn);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);


	IsGround = true;
}


// Called to bind functionality to input
// 입력 액션과 함수를 연결하는 함수
void APawnCharacter::SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 입력 매핑 컨텍스트가 설정되지 않았을 때 경고 로그 출력
	if (!MappingContext){
		UE_LOG(LogTemp, Warning, TEXT("No mapping context found"));
	}

	// 시점 회전 입력 액션이 없을 때 경고 로그 출력
	if (!IA_LOOK){
		UE_LOG(LogTemp, Warning, TEXT("No look at IA_LOOK"));
	}

	// 이동 입력 액션이 없을 때 경고 로그 출력
	if (!IA_MOVE){
		UE_LOG(LogTemp, Warning, TEXT("No look at IA_MOVE"));
	}
	if (!IA_RUN){
		UE_LOG(LogTemp, Warning, TEXT("No IA_RUN"));
	}

	// 현재 Pawn을 조종하는 Controller를 PlayerController로 변환
	if (APlayerController* PlayerController = Cast<APlayerController>(
			GetController())){
		// 로컬 플레이어의 Enhanced Input Subsystem을 가져옴
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
						PlayerController->GetLocalPlayer())){
			// 입력 매핑 컨텍스트를 등록해서 IA_MOVE, IA_LOOK 입력이 동작하게 함
			Subsystem->AddMappingContext(MappingContext, 0);
		}

		// 기본 입력 컴포넌트를 Enhanced Input 전용 컴포넌트로 변환
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<
			UEnhancedInputComponent>(PlayerInputComponent)){
			// IA_LOOK 입력이 발생하는 동안 Look 함수 실행
			EnhancedInputComponent->BindAction(
					IA_LOOK,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Look
					);

			// IA_MOVE 입력이 발생하는 동안 Move 함수 실행
			EnhancedInputComponent->BindAction(
					IA_MOVE,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Move
					);

			EnhancedInputComponent->BindAction(
					IA_RUN,
					ETriggerEvent::Started,
					this,
					&APawnCharacter::RunStart
					);
			EnhancedInputComponent->BindAction(
					IA_RUN,
					ETriggerEvent::Completed,
					this,
					&APawnCharacter::RunEnd
					);
		}
	}
}

// 이동 입력 처리 함수
void APawnCharacter::Move(const FInputActionValue& value)
{
	// float speed = IsRun ? (MovementSpeed * 1.5) : MovementSpeed;
	// 입력값을 2D 벡터로 가져옴
	// X, Y 값은 키보드 WASD나 스틱 입력 방향을 의미
	const FVector2D MoveInput = value.Get<FVector2D>();
	// 현재 입력값을 로그로 출력
	UE_LOG(LogTemp, Warning, TEXT("Move Input: %s"), *MoveInput.ToString());
	// 프레임 간 시간 차이
	// 프레임 수가 달라도 이동 속도를 일정하게 만들기 위해 사용
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	// 이동량 계산
	// 이동량 = 입력 방향 * 이동 속도 * DeltaTime
	// Z는 0으로 두어 위아래로는 움직이지 않음
	const FVector DeltaLocation = FVector(MoveInput.X, MoveInput.Y, 0.f) *
			MovementSpeed * DeltaTime;
	// Pawn을 로컬 좌표 기준으로 이동
	// true는 충돌 검사를 하면서 이동한다는 의미
	AddActorLocalOffset(DeltaLocation, true);
}


void APawnCharacter::RunStart(const FInputActionValue& value)
{
	IsRun = true;
}

void APawnCharacter::RunEnd(const FInputActionValue& value)
{
	IsRun = false;
}


// 마우스/시점 입력 처리 함수
void APawnCharacter::Look(const FInputActionValue& value)
{
	// 입력값을 2D 벡터로 가져옴
	// X는 좌우 회전, Y는 위아래 회전에 사용
	const FVector2D LookInput = value.Get<FVector2D>();
	// 프레임 보정을 위한 시간 값
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	// 마우스 감도 값
	constexpr float MouseSensitivity = 100.f;
	// 좌우 회전값 계산
	// Yaw = 좌우 입력값 * 감도 * DeltaTime
	const float YawValue = LookInput.X * MouseSensitivity * DeltaTime;
	// 위아래 회전값 계산
	// Pitch = 상하 입력값 * 감도 * DeltaTime
	const float PitchValue = LookInput.Y * MouseSensitivity * DeltaTime;
	// Pawn 자체를 좌우로 회전
	// FRotator(Pitch, Yaw, Roll) 순서이므로 Yaw만 적용
	AddActorLocalRotation(FRotator(0.f, YawValue, 0.f));

	// 스프링암의 현재 상대 회전값을 가져옴
	FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();

	// 카메라의 위아래 회전값을 계산하고 -80도 ~ 80도로 제한
	// 너무 위나 아래로 꺾여 카메라가 뒤집히는 것을 방지
	SpringArmRotation.Pitch = FMath::Clamp(
			SpringArmRotation.Pitch - PitchValue,
			-80.f,
			80.f
			);

	// 화면이 좌우로 기울어지지 않도록 Roll 값 고정
	SpringArmRotation.Roll = 0.f;
	// 계산된 회전값을 스프링암에 적용
	SpringArmComponent->SetRelativeRotation(SpringArmRotation);
}


bool APawnCharacter::GroundCheck()
{
	FHitResult GroundHit;
	constexpr float GroundCheckDistance = 10.0f;
	const float CapsuleHalfHeight = CapsuleComponent->
			GetScaledCapsuleHalfHeight();

	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.f, 0.f,
	                                    CapsuleHalfHeight +
	                                    GroundCheckDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	const bool Hit = GetWorld()->LineTraceSingleByChannel(
			GroundHit,
			Start,
			End,
			ECC_Visibility,
			QueryParams
			);

	const bool bHitGround = Hit
			&& ((GroundHit.GetActor() && GroundHit.GetActor()->ActorHasTag(
						"Ground"))
				|| (GroundHit.GetComponent() && GroundHit.GetComponent()->
				                                          ComponentHasTag("Ground")));
	const FColor DebugColor = bHitGround ? FColor::Green : FColor::Red;

	DrawDebugLine(GetWorld(), Start, End, DebugColor, false, 0.0f, 0, 2.0f);

	if (Hit){
		DrawDebugSphere(GetWorld(), GroundHit.ImpactPoint, 8.0f, 12, DebugColor,
		                false, 0.0f);
		IsGround = true;
		UE_LOG(LogTemp, Warning, TEXT("땅 "));
	}
	else{
		IsGround = false;
	}
	return IsGround;
}

void APawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Player"));
}

void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateGroundCheck();
	UpdateRun(DeltaTime);
	SetFalling();
}

void APawnCharacter::SetFalling()
{
	if (!IsGround){
		AddActorWorldOffset(FVector(0.0f, 0.0f, -10.0f), true);
		UE_LOG(LogTemp, Warning, TEXT("SET FALLING"));
	}
}

void APawnCharacter::UpdateGroundCheck()
{
	GroundCheck();
}

void APawnCharacter::UpdateRun(float DeltaTime)
{
	if (IsRun && Stamina > 0.f){
		MovementSpeed = MovementSpeedOriginal * RunMultiplier;
		StaminaCalcWithApply(DeltaTime, false);

		if (Stamina <= 0.f){
			MovementSpeed = MovementSpeedOriginal;
			StaminaCalcWithApply(DeltaTime, true);
		}
	}
	else{
		MovementSpeed = MovementSpeedOriginal;
		StaminaCalcWithApply(DeltaTime, true);
	}
}

void APawnCharacter::StaminaCalcWithApply(float DeltaTime, bool bShouldRecover)
{
	if (Stamina < StaminaMax && bShouldRecover){
		Stamina += StaminaIncrease * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Stamina: %f"), Stamina);
	}
	else if (Stamina > 0.f && !bShouldRecover){
		Stamina -= StaminaDecrease * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Stamina: %f"), Stamina);
	}
	Stamina = FMath::Clamp(Stamina, 0.0f, StaminaMax);
	OnStaminaChange.Broadcast(Stamina);
	UE_LOG(LogTemp, Warning, TEXT("Stamina BroadCast: %f"), Stamina);
}
