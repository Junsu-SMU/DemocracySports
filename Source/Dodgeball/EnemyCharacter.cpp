// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter); // SetTarget함수는 LookAtActorComponent.h에서 가져옴
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Look at the player character every frame
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget(); // CanSeeTarget함수는 LookAtActorComponent.h에서 가져옴

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnemyCharacter::ThrowDodgeball, // 사용할 함수
				ThrowingInterval, // 재장전 시간
				true, // 루프 여부
				ThrowingDelay); // 초기 딜레이
		}
		else
		{
			//Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle); // 타이머 초기화
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

void AEnemyCharacter::ThrowDodgeball() // 탄막 생성하고 던지는 함수
{
	if (DodgeballClass == nullptr) // 탄막이 무슨 클래스인지 정해지지 않으면 반환
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	//탄막 생성
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 1000.f; // 탄막 초기 속도
	Projectile->FinishSpawning(SpawnTransform);
}
