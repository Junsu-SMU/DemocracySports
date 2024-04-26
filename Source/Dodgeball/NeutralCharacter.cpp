// Fill out your copyright notice in the Description page of Project Settings.

#include "NeutralCharacter.h"
#include "HealthComponent.h"
#include "DodgeballCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"

// Sets default values
ANeutralCharacter::ANeutralCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANeutralCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter); // SetTarget�Լ��� LookAtActorComponent.h���� ������
}

// Called every frame
void ANeutralCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Look at the player character every frame
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget(); // CanSeeTarget�Լ��� LookAtActorComponent.h���� ������

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&ANeutralCharacter::ThrowDodgeball, // ����� �Լ�
				ThrowingInterval, // ������ �ð�
				true, // ���� ����
				ThrowingDelay); // �ʱ� ������
		}
		else
		{
			//Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle); // Ÿ�̸� �ʱ�ȭ
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

void ANeutralCharacter::ThrowDodgeball() // ź�� �����ϰ� ������ �Լ�
{
	if (DodgeballClass == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		return;
	}

	if (UHealthComponent::myVote < ADodgeballCharacter::neutralchangebuff) // ��ǥ���� ���غ��� ������ ź�� ��ô
	{
		FVector ForwardVector = GetActorForwardVector();
		float SpawnDistance = 40.f;
		FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		//ź�� ����
		ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

		Projectile->GetProjectileMovementComponent()->InitialSpeed = 1000.f; // ź�� �ʱ� �ӵ�
		Projectile->FinishSpawning(SpawnTransform);
	}
}


