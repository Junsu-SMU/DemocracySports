// Fill out your copyright notice in the Description page of Project Settings.


#include "VoteObject.h"
#include "Components/SphereComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
AVoteObject::AVoteObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	SphereComponent->OnComponentHit.AddDynamic(this, &AVoteObject::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

}

// Called when the game starts or when spawned
void AVoteObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVoteObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoteObject::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);

	if (Player != nullptr)
	{
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (HealthComponent != nullptr)
		{
			HealthComponent->GainVote(VoteUp); // HealthComponent에 있는 GainVote함수 실행
		}

		if (VoteGainSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, VoteGainSound);
		}
		Destroy(); // 맞고 난 후 탄막 삭제
		ASpawnObject::ReSpawn = true;
	}
}