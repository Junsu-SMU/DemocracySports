// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"

// Sets default values
AMusicManager::AMusicManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetUISound(true);
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();


	if (ADodgeballPlayerController::GameIn == true)
	{
		if (ADodgeballPlayerController::CurrentLevel == 0)
		{
			AudioComponent->SetSound(Stage1Sound);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 1)
		{
			AudioComponent->SetSound(Stage2Sound);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 2)
		{
			AudioComponent->SetSound(Stage3Sound);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 3)
		{
			AudioComponent->SetSound(Stage4Sound);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 4)
		{
			AudioComponent->SetSound(Stage5Sound);
		}
	}
	else
	{
		AudioComponent->SetSound(MainSound);
	}
	AudioComponent->Play();

}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusicManager::StopMusic()
{
	AudioComponent->Stop();
}

void AMusicManager::PlayMainSound()
{
	AudioComponent->SetSound(MainSound);
	AudioComponent->Play();
}
