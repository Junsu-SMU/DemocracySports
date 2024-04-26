// Fill out your copyright notice in the Description page of Project Settings.


#include "M3Object.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

bool AM3Object::M3delete = false;
bool AM3Object::M3Count = false;
float AM3Object::M3TimerElapsed = 0;

// Sets default values
AM3Object::AM3Object()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	HumanComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Human Component"));
	ConeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone Component"));
	ConeComponent->SetGenerateOverlapEvents(true);
	ConeComponent->SetSimulatePhysics(false);
	RootComponent = HumanComponent;
	ConeComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AM3Object::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AM3Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AM3Object::M3delete == true)
	{
		Destroy();
		AM3Object::M3TimerElapsed = 0;
	}

	AM3Object::M3TimerElapsed = GetWorldTimerManager().GetTimerElapsed(SeeTimerHandle);
	if (AM3Object::M3TimerElapsed < 0)
	{
		AM3Object::M3TimerElapsed = 0;
	}
}

void AM3Object::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("M3 In"));
		GetWorldTimerManager().SetTimer(SeeTimerHandle,
			this,
			&AM3Object::TimeInM3, // 사용할 함수
			ADodgeballCharacter::M3cleartime, // 쿨타임
			false); // 루프X

	}
}

void AM3Object::NotifyActorEndOverlap(AActor* OtherActor)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("M3 Out"));
		GetWorldTimerManager().ClearTimer(SeeTimerHandle);

	}
}

void AM3Object::TimeInM3()
{
	AM3Object::M3Count = true;
}
