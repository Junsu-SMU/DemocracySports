// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DodgeballCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "VoteObject.h"
#include "Components/StaticMeshComponent.h"


//////////////////////////////////////////////////////////////////////////
// ADodgeballCharacter

float ADodgeballCharacter::playerhp = 100.f;
float ADodgeballCharacter::playerspeed = 600.f;
float ADodgeballCharacter::playercooltime = 5.f;
float ADodgeballCharacter::M4cooltime = 2.5f;
float ADodgeballCharacter::M3cleartime = 7.5f;
bool ADodgeballCharacter::M1M2buff = false;
float ADodgeballCharacter::trapXtime = 10.f;
bool ADodgeballCharacter::healperminute = false;
float ADodgeballCharacter::neutralchangebuff = 15.f;
bool ADodgeballCharacter::buyitem1 = false;
bool ADodgeballCharacter::buyitem2 = false;
bool ADodgeballCharacter::buyitem3 = false;
bool ADodgeballCharacter::buyitem4 = false;
bool ADodgeballCharacter::buyitem5 = false;
bool ADodgeballCharacter::buyitem6 = false;
bool ADodgeballCharacter::buyitem7 = false;
bool ADodgeballCharacter::buyitem8 = false;
bool ADodgeballCharacter::buyitem9 = false;
bool ADodgeballCharacter::SlidingCooltime = false;

ADodgeballCharacter::ADodgeballCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement

	// Character moves in the direction of input...	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// ...at this rotation rate
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = ADodgeballCharacter::playerspeed;
	GetCharacterMovement()->MaxAcceleration = 2048.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// The camera follows at this distance behind the character
	CameraBoom->TargetArmLength = 2000.0f;
	//The camera looks down at the player
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	GoalArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalArrow"));
}

void ADodgeballCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookVote();

}

void ADodgeballCharacter::LookVote()
{
	FVector Start = GetActorLocation();
	FVector End;
	for (TActorIterator<AVoteObject> Iter(GetWorld()); Iter; ++Iter) // 월드에 있는 DodgeballCharacter 찾기
	{
		AVoteObject* VoteObj = *Iter; // Player 변수에 DodgeballCharacter 담기

		if (VoteObj != nullptr)
		{
			End = VoteObj->GetActorLocation();
		}
	}
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
	GoalArrow->SetWorldRotation(LookAtRotation);
}

void ADodgeballCharacter::OnDeath_Implementation()
{
	ADodgeballPlayerController::InGameMission = 0;
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->ShowRestartWidget();
	}
}

void ADodgeballCharacter::OnTakeDamage_Implementation()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
		PlayerController->UpdateVotePercent(HealthComponent->GetVotePercent());
	}
}

void ADodgeballCharacter::OnClear_Implementation()
{
	ADodgeballPlayerController::InGameMission = 0;
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->ShowClearWidget(HealthComponent->GetHealthPercent());
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADodgeballCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADodgeballCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADodgeballCharacter::MoveRight);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADodgeballCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADodgeballCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADodgeballCharacter::OnResetVR);
	PlayerInputComponent->BindAction("Sliding", IE_Pressed, this, &ADodgeballCharacter::Sliding);
}


void ADodgeballCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADodgeballCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ADodgeballCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ADodgeballCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADodgeballCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ADodgeballCharacter::Sliding()
{
	if ((Controller != NULL) && ADodgeballCharacter::SlidingCooltime == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Sliding"));

		GetCharacterMovement()->MaxWalkSpeed = 6000.f; // 순간적인 최대속도 증가
		GetCharacterMovement()->MaxAcceleration = 200000.f; // 순간적인 최대가속도 증가 
		GetCharacterMovement()->GetMaxAcceleration(); // 최대 가속도로 변경
		GetCharacterMovement()->GetMaxSpeed(); // 최대 속도로 변경

		if (SlidingSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, SlidingSound);
		}

		GetWorldTimerManager().SetTimer(MaxSpeedTimerHandle,
			this,
			&ADodgeballCharacter::MaxSpeed, // 사용할 함수
			0.1, // 쿨타임
			false); // 루프X

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 10000.f); // 100 거리를 이동

		ADodgeballCharacter::SlidingCooltime = true; // 쿨타임on
		
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
		PlayerController->SlidingOn();

		GetWorldTimerManager().SetTimer(SlidingTimerHandle,
			this,
			&ADodgeballCharacter::CoolDown, // 사용할 함수
			ADodgeballCharacter::playercooltime, // 쿨타임
			false); // 루프X
	}
	else
		UE_LOG(LogTemp, Log, TEXT("please wait cooltime"));
}

void ADodgeballCharacter::CoolDown()
{
	UE_LOG(LogTemp, Log, TEXT("Sliding CoolUp"));
	ADodgeballCharacter::SlidingCooltime = false;
	GetWorldTimerManager().ClearTimer(SlidingTimerHandle); // 타이머 초기화
}

void ADodgeballCharacter::MaxSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = ADodgeballCharacter::playerspeed;
	GetCharacterMovement()->MaxAcceleration = 2048.f;
	GetWorldTimerManager().ClearTimer(MaxSpeedTimerHandle); // 타이머 초기화
}
