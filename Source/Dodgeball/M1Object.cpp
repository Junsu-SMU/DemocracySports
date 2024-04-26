// Fill out your copyright notice in the Description page of Project Settings.


#include "M1Object.h"
#include "Components/CapsuleComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

int AM1Object::M1Count = 0;
bool AM1Object::M1delete = false;

// Sets default values
AM1Object::AM1Object()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	CapsuleComponent->SetCollisionProfileName(FName("Dodgeball"));
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AM1Object::OnHit);
	RootComponent = CapsuleComponent;
}

// Called when the game starts or when spawned
void AM1Object::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AM1Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AM1Object::M1delete == true)
	{
		Destroy();
	}

}

void AM1Object::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);

	if (Player != nullptr)
	{
		if (M1touchSound1 != nullptr && M1touchSound2 != nullptr)
		{
			int a = rand();
			if (a % 2 == 1)
			{
				UGameplayStatics::PlaySound2D(this, M1touchSound1);
			}
			else
			{
				UGameplayStatics::PlaySound2D(this, M1touchSound2);
			}
		}
		Destroy(); // 닿고 난 후 액터 삭제
		AM1Object::M1Count += 1;
		UE_LOG(LogTemp, Log, TEXT("M1Count Up"));
	}
}