// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObject.h"
#include "Engine/World.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "random"
#include "iostream"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "VoteObject.h"
#include "DodgeballPlayerController.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "M1Object.h"
#include "M2Object.h"
#include "M2Base.h"
#include "M3Object.h"
#include "M4Object.h"
#include "TrapObject.h"
#include "FoodObject.h"

bool ASpawnObject::ReSpawn = false;
bool ASpawnObject::TrapSpawn = false;
bool ASpawnObject::FoodSpawn = false;
std::random_device rng;
std::uniform_real_distribution<float> dist0(0, 100.f);
std::uniform_real_distribution<float> dist(-900.f, 900.f); // 1000
std::uniform_real_distribution<float> dist2(-1200.f, 1200.f); // 1300
std::uniform_real_distribution<float> dist3(-1400.f, 1400.f); // 1500
std::uniform_real_distribution<float> dist4(0, 360.f);
std::uniform_real_distribution<float> dist5(-1900.f, 1900.f); // 2000

// Sets default values
ASpawnObject::ASpawnObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();

	prex = 0;
	prey = 0;
	trapx = 0;
	trapy = 0;
	
	AM2Object::M2Put = false;

	SpawnVote();
	SpawnTrap();
	SpawnFood();

	GetWorldTimerManager().SetTimer(MissionTimerHandle,
		this,
		&ASpawnObject::MissionRand, // ����� �Լ�
		30, // ��Ÿ��
		true, // ����
		15); // ó�� �����Ҷ��� 15�� ��

}

// Called every frame
void ASpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ASpawnObject::ReSpawn == true)
	{
		ASpawnObject::ReSpawn = false;
		SpawnVote();
	}

	if (ASpawnObject::TrapSpawn == true)
	{
		ASpawnObject::TrapSpawn = false;
		SpawnTrap();
	}

	if (ASpawnObject::FoodSpawn == true)
	{
		ASpawnObject::FoodSpawn = false;
		SpawnFood();
	}

	if (AM1Object::M1Count == 4)
	{
		UE_LOG(LogTemp, Log, TEXT("Mission Clear"));
		MissionClear();
		if (ADodgeballCharacter::M1M2buff == true)
		{
			for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
			{
				ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���

				if (Player != nullptr)
				{
					UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
					if (HealthComponent != nullptr)
					{
						HealthComponent->LoseHealth(-10); // HealthComponent�� �ִ� LoseVote�Լ� ����
					}
				}
			}
		}
		AM1Object::M1Count = 0;
	}

	if (AM2Base::M2Count == 3)
	{
		UE_LOG(LogTemp, Log, TEXT("Mission Clear"));
		MissionClear();
		if (ADodgeballCharacter::M1M2buff == true)
		{
			for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
			{
				ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���

				if (Player != nullptr)
				{
					UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
					if (HealthComponent != nullptr)
					{
						HealthComponent->LoseHealth(-10); // HealthComponent�� �ִ� LoseVote�Լ� ����
					}
				}
			}
		}
		AM2Base::M2Count = 0;
	}

	if (AM3Object::M3Count == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Mission Clear"));
		MissionClear();
		AM3Object::M3Count = false;
	}

	if (AM4Object::M4Count == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Got Damaged"));
		AM4Object::M4Count = false;
		Timeover();
	}

	if (ADodgeballPlayerController::InGameMission == 1)
	{
		for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
		{
			ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
			if (Player != nullptr)
			{
				ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
				if (PlayerController != nullptr)
				{
					float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(TimeoverHandle);
					PlayerController->UpdateMission(1, AM1Object::M1Count, 4, 15-GameTimerElapsed, AM1Object::M1Count/4);
				}
			}
		}
	}
	else if (ADodgeballPlayerController::InGameMission == 2)
	{
		for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
		{
			ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
			if (Player != nullptr)
			{
				ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
				if (PlayerController != nullptr)
				{
					float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(TimeoverHandle);
					PlayerController->UpdateMission(2, AM2Base::M2Count, 3, 15 - GameTimerElapsed, AM2Base::M2Count / 3);
				}
			}
		}
	}
	else if (ADodgeballPlayerController::InGameMission == 3)
	{
		for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
		{
			ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
			if (Player != nullptr)
			{
				ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
				if (PlayerController != nullptr)
				{
					float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(TimeoverHandle);
					PlayerController->UpdateMission(3, AM3Object::M3TimerElapsed, ADodgeballCharacter::M3cleartime, 15 - GameTimerElapsed, AM3Object::M3TimerElapsed / ADodgeballCharacter::M3cleartime);
				}
			}
		}
	}
	else if (ADodgeballPlayerController::InGameMission == 4)
	{
		for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
		{
			ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
			if (Player != nullptr)
			{
				ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
				if (PlayerController != nullptr)
				{
					float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(M4Handle);
					PlayerController->UpdateMission(4, 0, 0, 15 - GameTimerElapsed, 0);
				}
			}
		}
	}

}

void ASpawnObject::SpawnVote()
{
	ASpawnObject::ReSpawn = false;

	if (VoteClass == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("VoteClass is nullptr"));
		return;
	}

	bool go = true;

	if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x * x + y * y <= 1100 * 1100)
				{
					go = false;
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist3(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x >= 0 && y >= 0)
				{
					if (y <= -x + 1400)
					{
						go = false;
					}
				}
				else if (x >= 0 && y <= 0)
				{
					if (y >= x - 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y >= 0)
				{
					if (y <= x + 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y <= 0)
				{
					if (y >= -x - 1400)
					{
						go = false;
					}
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist5(rng);
			y = dist5(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
				{
					go = true;
				}
				else
				{
					go = false;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Level search error"));
		x = 0;
		y = 0;
	}
	prex = x;
	prey = y;

	FVector SpawnLocation = GetActorLocation() + FVector(y, x, 50);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AVoteObject* VoteObject = GetWorld()->SpawnActorDeferred<AVoteObject>(VoteClass, SpawnTransform);
	VoteObject->FinishSpawning(SpawnTransform);
}

void ASpawnObject::SpawnTrap()
{
	ASpawnObject::TrapSpawn = false;

	if (TrapClass == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("TrapClass is nullptr"));
		return;
	}

	bool go = true;

	if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist(rng);
			if ((x - trapx) * (x - trapx) + (y - trapy) * (y - trapy) >= 1000 * 1000) //������ �Ÿ��� 500 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - prex) * (x - prex) + (y - prey) * (y - prey) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x * x + y * y <= 1100 * 1100)
				{
					go = false;
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - trapx) * (x - trapx) + (y - trapy) * (y - trapy) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist3(rng);
			if ((x - trapx) * (x - trapx) + (y - trapy) * (y - trapy) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x >= 0 && y >= 0)
				{
					if (y <= -x + 1400)
					{
						go = false;
					}
				}
				else if (x >= 0 && y <= 0)
				{
					if (y >= x - 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y >= 0)
				{
					if (y <= x + 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y <= 0)
				{
					if (y >= -x - 1400)
					{
						go = false;
					}
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist5(rng);
			y = dist5(rng);
			if ((x - trapx) * (x - trapx) + (y - trapy) * (y - trapy) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
				{
					go = true;
				}
				else
				{
					go = false;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Level search error"));
		x = 0;
		y = 0;
	}
	trapx = x;
	trapy = y;

	FVector SpawnLocation = GetActorLocation() + FVector(y, x, 50);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	ATrapObject* TrapObject = GetWorld()->SpawnActorDeferred<ATrapObject>(TrapClass, SpawnTransform);
	TrapObject->FinishSpawning(SpawnTransform);
	UE_LOG(LogTemp, Log, TEXT("Trap Spawned"));
}

void ASpawnObject::SpawnFood()
{
	ASpawnObject::FoodSpawn = false;

	if (FoodClass == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("FoodClass is nullptr"));
		return;
	}

	bool go = true;

	if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist(rng);
			if ((x - foodx) * (x - foodx) + (y - foody) * (y - foody) >= 1000 * 1000) //������ �Ÿ��� 500 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - foodx) * (x - foodx) + (y - foody) * (y - foody) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x * x + y * y <= 1100 * 1100)
				{
					go = false;
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if ((x - foodx) * (x - foodx) + (y - foody) * (y - foody) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist3(rng);
			if ((x - foodx) * (x - foodx) + (y - foody) * (y - foody) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if (x >= 0 && y >= 0)
				{
					if (y <= -x + 1400)
					{
						go = false;
					}
				}
				else if (x >= 0 && y <= 0)
				{
					if (y >= x - 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y >= 0)
				{
					if (y <= x + 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y <= 0)
				{
					if (y >= -x - 1400)
					{
						go = false;
					}
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist5(rng);
			y = dist5(rng);
			if ((x - foodx) * (x - foodx) + (y - foody) * (y - foody) >= 1000 * 1000) //������ �Ÿ��� 1000 �̻��̸� ���
			{
				if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
				{
					go = true;
				}
				else
				{
					go = false;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Level search error"));
		x = 0;
		y = 0;
	}
	foodx = x;
	foody = y;

	FVector SpawnLocation = GetActorLocation() + FVector(y, x, 50);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	AFoodObject* FoodObject = GetWorld()->SpawnActorDeferred<AFoodObject>(FoodClass, SpawnTransform);
	FoodObject->FinishSpawning(SpawnTransform);
	UE_LOG(LogTemp, Log, TEXT("Food Spawned"));
}

void ASpawnObject::MissionRand()
{
	UE_LOG(LogTemp, Log, TEXT("Mission Randomly Selected"));
	float rand = 0;
	bool in4 = false;
	rand = dist0(rng);

	if (rand <= 25)
	{
		AM1Object::M1delete = false;
		ADodgeballPlayerController::InGameMission = 1;
		SpawnM1();
	}
	else if (rand <= 50)
	{
		AM2Base::M2delete = false;
		AM2Object::M2Put = false;
		ADodgeballPlayerController::InGameMission = 2;
		SpawnM2();
	}
	else if (rand <= 75)
	{
		AM3Object::M3delete = false;
		ADodgeballPlayerController::InGameMission = 3;
		SpawnM3();
	}
	else if (75 < rand)
	{
		AM4Object::M4delete = false;
		ADodgeballPlayerController::InGameMission = 4;
		in4 = true;
		SpawnM4();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Mission error"));
	}

	if (in4 == true)
	{
		GetWorldTimerManager().SetTimer(M4SpawnHandle,
			this,
			&ASpawnObject::SpawnM4, // ����� �Լ�
			ADodgeballCharacter::M4cooltime, // ��Ÿ��
			true); // ����O

		GetWorldTimerManager().SetTimer(M4Handle,
			this,
			&ASpawnObject::MissionClear, // ����� �Լ�
			15, // ��Ÿ��
			false); // ����X
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimeoverHandle,
			this,
			&ASpawnObject::Timeover, // ����� �Լ�
			15, // ��Ÿ��
			false); // ����X
	}

	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
	{
		ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
		if (Player != nullptr)
		{
			ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
			if (PlayerController != nullptr)
			{
				PlayerController->ShowHUDStart();
				GetWorldTimerManager().SetTimer(HidingHandle,
					this,
					&ASpawnObject::Hiding, // ����� �Լ�
					3, // ��Ÿ��
					false); // ����X
			}
		}
	}

}

void ASpawnObject::Hiding()
{
	GetWorldTimerManager().ClearTimer(HidingHandle);
	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
	{
		ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���
		if (Player != nullptr)
		{
			ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
			if (PlayerController != nullptr)
			{
				PlayerController->Hiding();
			}
		}
	}
}

void ASpawnObject::Timeover()
{
	GetWorldTimerManager().ClearTimer(TimeoverHandle);
	GetWorldTimerManager().ClearTimer(M4Handle);
	GetWorldTimerManager().ClearTimer(M4SpawnHandle);
	
	UE_LOG(LogTemp, Log, TEXT("Timeover in"));
	ADodgeballPlayerController::InGameMission = 0;

	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
	{
		ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���

		if (Player != nullptr)
		{

			if (MissionFailSound != nullptr)
			{
				UGameplayStatics::PlaySound2D(Player, MissionFailSound);
			}

			UE_LOG(LogTemp, Log, TEXT("Player find"));
			UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
			if (HealthComponent != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("healthcomponent find"));
				HealthComponent->LoseVote(5); // HealthComponent�� �ִ� LoseVote�Լ� ����
			}
			ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
			if (PlayerController != nullptr)
			{
				float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(M4Handle);
				PlayerController->UpdateMission(0, 0, 0, 0, 0);
				PlayerController->ShowHUDLose();
				GetWorldTimerManager().SetTimer(HidingHandle,
					this,
					&ASpawnObject::Hiding, // ����� �Լ�
					3, // ��Ÿ��
					false); // ����X
			}
		}
	}

	// �̼� ������Ʈ�� �����ϱ�
	AM1Object::M1delete = true; // �̼�1 ������Ʈ ����
	AM2Base::M2delete = true; // �̼�2 ������Ʈ ����
	AM3Object::M3delete = true; // �̼�3 ������Ʈ ����
	AM4Object::M4delete = true; // �̼�4 ������Ʈ ����
}

void ASpawnObject::MissionClear()
{
	GetWorldTimerManager().ClearTimer(TimeoverHandle);
	GetWorldTimerManager().ClearTimer(M4Handle);
	GetWorldTimerManager().ClearTimer(M4SpawnHandle);
	UE_LOG(LogTemp, Log, TEXT("MissionClear in"));

	ADodgeballPlayerController::InGameMission = 0;

	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
	{
		ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���

		if (Player != nullptr)
		{

			if (MissionClearSound != nullptr)
			{
				UGameplayStatics::PlaySound2D(Player, MissionClearSound);
			}

			UE_LOG(LogTemp, Log, TEXT("Player find"));
			UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
			if (HealthComponent != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("healthcomponent find"));
				HealthComponent->GainVote(5); // HealthComponent�� �ִ� GainVote�Լ� ����
			}
			ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(Player->GetController());
			if (PlayerController != nullptr)
			{
				float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(M4Handle);
				PlayerController->UpdateMission(0, 0, 0, 0, 0);
				PlayerController->ShowHUDClear();
				GetWorldTimerManager().SetTimer(HidingHandle,
					this,
					&ASpawnObject::Hiding, // ����� �Լ�
					3, // ��Ÿ��
					false); // ����X
			}
		}
	}

	// �̼� ������Ʈ�� �����ϱ�
	AM1Object::M1delete = true; // �̼�1 ������Ʈ ����
	AM2Base::M2delete = true; // �̼�2 ������Ʈ ����
	AM3Object::M3delete = true; // �̼�3 ������Ʈ ����
	AM4Object::M4delete = true; // �̼�4 ������Ʈ ����
}

void ASpawnObject::SpawnM1()
{
	AM1Object::M1Count = 0; // �̼� ī��Ʈ�� 0���� �ʱ�ȭ

	if (M1Class == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("M1Class is nullptr"));
		return;
	}

	bool go = true;

	for (int a = 0; a < 4; a++)
	{
		go = true;

		if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
		{
			x = dist3(rng);
			y = dist(rng);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist2(rng);
				y = dist2(rng);
				if (x * x + y * y <= 1100 * 1100)
				{
					go = false;
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
		{
			x = dist2(rng);
			y = dist2(rng);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist3(rng);
				y = dist3(rng);
				if (x >= 0 && y >= 0)
				{
					if (y <= -x + 1400)
					{
						go = false;
					}
				}
				else if (x >= 0 && y <= 0)
				{
					if (y >= x - 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y >= 0)
				{
					if (y <= x + 1400)
					{
						go = false;
					}
				}
				else if (x <= 0 && y <= 0)
				{
					if (y >= -x - 1400)
					{
						go = false;
					}
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist5(rng);
				y = dist5(rng);
				if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
				{
					go = true;
				}
				else
				{
					go = false;
				}
			}
		}

		FVector SpawnLocation = GetActorLocation() + FVector(y, x, 110);
		FRotator SpawnRotation = FRotator(0, dist4(rng), 0);
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);

		UE_LOG(LogTemp, Log, TEXT("M1 is respawned"));

		AM1Object* M1Object = GetWorld()->SpawnActorDeferred<AM1Object>(M1Class, SpawnTransform);
		M1Object->FinishSpawning(SpawnTransform);
	}

}

void ASpawnObject::SpawnM2()
{
	AM2Base::M2Count = 0; // �̼� ī��Ʈ�� 0���� �ʱ�ȭ

	if (M2ObjectClass == nullptr || M2BaseClass == nullptr) // ������ ���Ͱ� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("Class is nullptr"));
		return;
	}

	bool go = true;
	int a = 0;
	float basex = 0;
	float basey = 0;

	for (a = 0; a < 4; a++)
	{
		go = true;

		if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist3(rng);
				y = dist(rng);
				if ((x - basex) * (x - basex) + (y - basey) * (y - basey) >= 200 * 200)
				{
					go = false;
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
		{
			while(go == true)
			{
				x = dist2(rng);
				y = dist2(rng);
				if (x * x + y * y <= 1100 * 1100)
				{
					if ((x - basex) * (x - basex) + (y - basey) * (y - basey) >= 200 * 200)
					{
						go = false;
					}
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist2(rng);
				y = dist2(rng);
				if ((x - basex) * (x - basex) + (y - basey) * (y - basey) >= 200 * 200)
				{
					go = false;
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist3(rng);
				y = dist3(rng);

				if ((x - basex) * (x - basex) + (y - basey) * (y - basey) >= 200 * 200)
				{
					if (x >= 0 && y >= 0)
					{
						if (y <= -x + 1400)
						{
							go = false;
						}
					}
					else if (x >= 0 && y <= 0)
					{
						if (y >= x - 1400)
						{
							go = false;
						}
					}
					else if (x <= 0 && y >= 0)
					{
						if (y <= x + 1400)
						{
							go = false;
						}
					}
					else if (x <= 0 && y <= 0)
					{
						if (y >= -x - 1400)
						{
							go = false;
						}
					}
				}
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
		{
			while (go == true)
			{
				x = dist5(rng);
				y = dist5(rng);
				if ((x - basex) * (x - basex) + (y - basey) * (y - basey) >= 200 * 200)
				{
					if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
					{
						go = true;
					}
					else
					{
						go = false;
					}
				}
			}
		}

		if (a == 0)
		{
			if (x >= 0)
			{
				x -= 150;
			}
			else
			{
				x += 150;
			}

			if (y >= 0)
			{
				y -= 150;
			}
			else
			{
				y += 150;
			}
			basex = x;
			basey = y;
		}

		FVector SpawnLocation = GetActorLocation() + FVector(y, x, 110);
		FRotator SpawnRotation = FRotator(0, dist4(rng), 0);
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);

		UE_LOG(LogTemp, Log, TEXT("Actor is respawned"));
		if (a == 0)
		{
			AM2Base* M2Base = GetWorld()->SpawnActorDeferred<AM2Base>(M2BaseClass, SpawnTransform);
			M2Base->FinishSpawning(SpawnTransform);
		}
		else
		{
			AM2Object* M2Object = GetWorld()->SpawnActorDeferred<AM2Object>(M2ObjectClass, SpawnTransform);
			M2Object->FinishSpawning(SpawnTransform);
		}

	}


}

void ASpawnObject::SpawnM3()
{
	AM3Object::M3Count = false; // �̼� ī��Ʈ�� 0���� �ʱ�ȭ

	if (M3Class == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("M3Class is nullptr"));
		return;
	}

	bool go = true;

	if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
	{
		x = dist3(rng);
		y = dist(rng);
	}
	else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist2(rng);
			y = dist2(rng);
			if (x * x + y * y <= 1100 * 1100)
			{
				go = false;
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
	{
		x = dist2(rng);
		y = dist2(rng);
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist3(rng);
			y = dist3(rng);
			if (x >= 0 && y >= 0)
			{
				if (y <= -x + 1400)
				{
					go = false;
				}
			}
			else if (x >= 0 && y <= 0)
			{
				if (y >= x - 1400)
				{
					go = false;
				}
			}
			else if (x <= 0 && y >= 0)
			{
				if (y <= x + 1400)
				{
					go = false;
				}
			}
			else if (x <= 0 && y <= 0)
			{
				if (y >= -x - 1400)
				{
					go = false;
				}
			}
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
	{
		while (go == true)
		{
			x = dist5(rng);
			y = dist5(rng);
			if ((x >= 400 || x <= -400) && (y >= 400 || y <= -400))
			{
				go = true;
			}
			else
			{
				go = false;
			}
		}
	}

	FVector SpawnLocation = GetActorLocation() + FVector(y, x, 10);
	FRotator SpawnRotation = FRotator(0, dist4(rng), 0);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	UE_LOG(LogTemp, Log, TEXT("M3 is respawned"));

	AM3Object* M3Object = GetWorld()->SpawnActorDeferred<AM3Object>(M3Class, SpawnTransform);
	M3Object->FinishSpawning(SpawnTransform);

}

void ASpawnObject::SpawnM4()
{
	AM4Object::M4Count = false; // �̼� ī��Ʈ�� 0���� �ʱ�ȭ

	if (M4Class == nullptr) // ź���� ���� Ŭ�������� �������� ������ ��ȯ
	{
		UE_LOG(LogTemp, Log, TEXT("M4Class is nullptr"));
		return;
	}

	float k = 0;
	k = dist0(rng); // k�� 0~100 ����
	FVector SpawnLocation = FVector(0, 0, 0);

	if (ADodgeballPlayerController::CurrentLevel == 0) // 1���� �������� ���� ��ǥ
	{
		if (k <= 25)
		{
			SpawnLocation = GetActorLocation() + FVector(800, 1300, 75);
		}
		else if (k <= 50)
		{
			SpawnLocation = GetActorLocation() + FVector(800, -1300, 75);
		}
		else if (k <= 75)
		{
			SpawnLocation = GetActorLocation() + FVector(-800, 1300, 75);
		}
		else
		{
			SpawnLocation = GetActorLocation() + FVector(-800, -1300, 75);
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 1) // 2���� �������� ���� ��ǥ
	{
		if (k <= 25)
		{
			SpawnLocation = GetActorLocation() + FVector(1000, 0, 75);
		}
		else if (k <= 50)
		{
			SpawnLocation = GetActorLocation() + FVector(0, -1000, 75);
		}
		else if (k <= 75)
		{
			SpawnLocation = GetActorLocation() + FVector(0, 1000, 75);
		}
		else
		{
			SpawnLocation = GetActorLocation() + FVector(-1000, 0, 75);
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2) // 3���� �������� ���� ��ǥ
	{
		if (k <= 25)
		{
			SpawnLocation = GetActorLocation() + FVector(1000, 1000, 75);
		}
		else if (k <= 50)
		{
			SpawnLocation = GetActorLocation() + FVector(1000, -1000, 75);
		}
		else if (k <= 75)
		{
			SpawnLocation = GetActorLocation() + FVector(-1000, 1000, 75);
		}
		else
		{
			SpawnLocation = GetActorLocation() + FVector(-1000, -1000, 75);
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3) // 4���� �������� ���� ��ǥ
	{
		if (k <= 25)
		{
			SpawnLocation = GetActorLocation() + FVector(1200, 0, 75);
		}
		else if (k <= 50)
		{
			SpawnLocation = GetActorLocation() + FVector(-1200, 0, 75);
		}
		else if (k <= 75)
		{
			SpawnLocation = GetActorLocation() + FVector(0, 1200, 75);
		}
		else
		{
			SpawnLocation = GetActorLocation() + FVector(0, -1200, 75);
		}
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4) // 5���� �������� ���� ��ǥ
	{
		SpawnLocation = GetActorLocation() + FVector(0, 0, 75);
	}

	FRotator SpawnRotation = FRotator(0, 0, 0);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	UE_LOG(LogTemp, Log, TEXT("M4 is respawned"));

	AM4Object* M4Object = GetWorld()->SpawnActorDeferred<AM4Object>(M4Class, SpawnTransform);
	M4Object->FinishSpawning(SpawnTransform);
}