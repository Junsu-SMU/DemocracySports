// Fill out your copyright notice in the Description page of Project Settings.


#include "M2Object.h"
#include "Components/SphereComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "M2Base.h"

bool AM2Object::M2Put = false;

// Sets default values
AM2Object::AM2Object()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AM2Object::OnHit);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void AM2Object::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AM2Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AM2Base::M2delete == true)
	{
		Destroy();
	}

}

void AM2Object::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);

	if (Player != nullptr && AM2Object::M2Put == false)
	{
		if (M2touchSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, M2touchSound);
		}
		Destroy(); // 닿고 난 후 액터 삭제
		AM2Object::M2Put = true;
		UE_LOG(LogTemp, Log, TEXT("M2Put Up"));
	}
}
