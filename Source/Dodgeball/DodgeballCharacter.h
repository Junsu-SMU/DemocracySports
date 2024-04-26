// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "HealthInterface.h"
#include "DodgeballCharacter.generated.h"

UCLASS(config = Game)
class ADodgeballCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *GoalArrow;

	class UHealthComponent* HealthComponent;

public:
	ADodgeballCharacter();

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;
	virtual void OnClear_Implementation() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	virtual void Tick(float DeltaTime) override;

protected:

	void LookVote();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Sliding();

	void CoolDown();

	void MaxSpeed();

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	FTimerHandle SlidingTimerHandle;
	FTimerHandle MaxSpeedTimerHandle;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* SlidingSound;

public:

	static float playerhp; // Store 능력 관련 변수들
	static float playerspeed;
	static float playercooltime;
	static float M4cooltime;
	static float M3cleartime;
	static bool M1M2buff;
	static float trapXtime;
	static bool healperminute;
	static float neutralchangebuff;
	static bool buyitem1;
	static bool buyitem2;
	static bool buyitem3;
	static bool buyitem4;
	static bool buyitem5;
	static bool buyitem6;
	static bool buyitem7;
	static bool buyitem8;
	static bool buyitem9;
	static bool SlidingCooltime;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

