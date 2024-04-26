// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodObject.h"
#include "Components/SphereComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
AFoodObject::AFoodObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	SphereComponent->OnComponentHit.AddDynamic(this, &AFoodObject::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

}

// Called when the game starts or when spawned
void AFoodObject::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FoodTimerHandle,
		this,
		&AFoodObject::LifeTimeEnd, // ����� �Լ�
		10, // ��Ÿ��
		false);
	
}

// Called every frame
void AFoodObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodObject::OnHit(UPrimitiveComponent* HitComp, // ź���� �ǰ��� �Ǹ� ����
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
			HealthComponent->LoseHealth(-5); // HealthComponent�� �ִ� LoseHealth�Լ� ����
		}
		if (FoodSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, FoodSound);
		}
		Destroy(); // �°� �� �� ź�� ����
		ASpawnObject::FoodSpawn = true;
	}
}

void AFoodObject::LifeTimeEnd()
{
	Destroy();
	ASpawnObject::FoodSpawn = true;
}
