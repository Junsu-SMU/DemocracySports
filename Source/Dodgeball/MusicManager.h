// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"

UCLASS()
class DODGEBALL_API AMusicManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMusicManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* MainSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* Stage1Sound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* Stage2Sound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* Stage3Sound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* Stage4Sound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* Stage5Sound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StopMusic();
	void PlayMainSound();

};
