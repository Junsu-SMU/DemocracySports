// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ADodgeballProjectile::ADodgeballProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1000.f;
}

void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.f);
}

void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeballProjectile::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
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
			HealthComponent->LoseHealth(Damage); // HealthComponent에 있는 LoseHealth함수 실행
			HealthComponent->LoseVote(VoteDown); // HealthComponent에 있는 LoseVote함수 실행 
		}

		if (DamageSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, DamageSound);
		}
		Destroy(); // 맞고 난 후 탄막 삭제
	}
}


