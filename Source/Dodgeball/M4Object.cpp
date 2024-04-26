// Fill out your copyright notice in the Description page of Project Settings.


#include "M4Object.h"
#include "Components/BoxComponent.h"
#include "DodgeballCharacter.h"
#include "Wall.h"
#include "HealthComponent.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "EngineUtils.h"

bool AM4Object::M4delete = false;
bool AM4Object::M4Count = false;

// Sets default values
AM4Object::AM4Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentHit.AddDynamic(this, &AM4Object::OnHit);
	RootComponent = BoxComponent;

}

// Called when the game starts or when spawned
void AM4Object::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // 월드에 있는 DodgeballCharacter 찾기
	{
		ADodgeballCharacter* Player = *Iter; // Player 변수에 DodgeballCharacter 담기

		if (Player != nullptr)
		{
			FVector CharVector = Player->GetActorLocation();
			FVector MyVector = GetActorLocation();

			CharVector.Z = 0;
			MyVector.Z = 0; // Z값을 통일

			FinalRotator = UKismetMathLibrary::FindLookAtRotation(MyVector, CharVector);
			AddActorWorldRotation(FinalRotator);
		}
	}
	
}

// Called every frame
void AM4Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector()*DeltaTime*720);

	if (AM4Object::M4delete == true)
	{
		Destroy();
	}

}

void AM4Object::OnHit(UPrimitiveComponent* HitComp, // 탄막에 피격이 되면 실행
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(OtherActor);

	if (Player != nullptr)
	{
		if (M4touchSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, M4touchSound);
		}
		Destroy(); // 닿고 난 후 액터 삭제
		AM4Object::M4Count = true;
		UE_LOG(LogTemp, Log, TEXT("M4 Hit"));
	}

	AWall* Wall = Cast<AWall>(OtherActor);

	if (Wall != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Wall Hit"));
		Destroy(); // 닿고 난 후 액터 삭제
	}

}
