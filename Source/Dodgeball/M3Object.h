// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "M3Object.generated.h"

UCLASS()
class DODGEBALL_API AM3Object : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* HumanComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ConeComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	FTimerHandle SeeTimerHandle;

public:
	AM3Object();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static bool M3Count;
	static bool M3delete;
	static float M3TimerElapsed;

	void TimeInM3();

};
