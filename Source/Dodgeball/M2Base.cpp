// Fill out your copyright notice in the Description page of Project Settings.


#include "M2Base.h"
#include "Components/BoxComponent.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "M2Object.h"

bool AM2Base::M2delete = false;
int AM2Base::M2Count = 0;

// Sets default values
AM2Base::AM2Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetCollisionProfileName(FName("Dodgeball"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentHit.AddDynamic(this, &AM2Base::OnHit);
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AM2Base::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AM2Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AM2Base::M2delete == true)
	{
		Destroy();
	}

}

void AM2Base::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);

	if (Player != nullptr && AM2Object::M2Put == true)
	{
		if (M2BaseSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, M2BaseSound);
		}
		//Destroy(); // 닿고 난 후 액터 삭제
		AM2Object::M2Put = false;
		AM2Base::M2Count += 1;
		UE_LOG(LogTemp, Log, TEXT("M2Put Up"));
	}
}
