// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapObject.h"
#include "Components/SphereComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
ATrapObject::ATrapObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	SphereComponent->OnComponentHit.AddDynamic(this, &ATrapObject::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

}

// Called when the game starts or when spawned
void ATrapObject::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TrapTimerHandle,
		this,
		&ATrapObject::LifeTimeEnd, // ����� �Լ�
		ADodgeballCharacter::trapXtime, // ��Ÿ��
		false);
	
}

// Called every frame
void ATrapObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapObject::OnHit(UPrimitiveComponent* HitComp, // ź���� �ǰ��� �Ǹ� ����
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
			HealthComponent->LoseHealth(10); // HealthComponent�� �ִ� LoseHealth�Լ� ����
		}
		if (TrapSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, TrapSound);
		}
		Destroy(); // �°� �� �� ź�� ����
		ASpawnObject::TrapSpawn = true;
	}
}

void ATrapObject::LifeTimeEnd()
{
	Destroy();
	ASpawnObject::TrapSpawn = true;
}
