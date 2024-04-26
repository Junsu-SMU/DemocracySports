// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObject.generated.h"

UCLASS()
class DODGEBALL_API ASpawnObject : public AActor
{
	GENERATED_BODY()

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle MissionTimerHandle;
	FTimerHandle TimeoverHandle;
	FTimerHandle M4Handle;
	FTimerHandle M4SpawnHandle;
	FTimerHandle HidingHandle;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* MissionClearSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* MissionFailSound;

public:
	ASpawnObject();

	virtual void Tick(float DeltaTime) override;

	void Hiding();
	void SpawnVote();
	void SpawnTrap();
	void SpawnFood();
	void SpawnM1();
	void SpawnM2();
	void SpawnM3();
	void SpawnM4();
	void MissionRand();
	void Timeover();
	void MissionClear();
	static bool ReSpawn;
	static bool TrapSpawn;
	static bool FoodSpawn;
	float prex = 0;
	float prey = 0;
	float trapx = 0;
	float trapy = 0;
	float foodx = 0;
	float foody = 0;

	float x = 0;
	float y = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = VotePoint)
		TSubclassOf<class AVoteObject> VoteClass; // 탄막의 클래스 정의하는 변수=VoteClass

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = M1)
		TSubclassOf<class AM1Object> M1Class; // 미션1의 클래스를 정의

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = M2)
		TSubclassOf<class AM2Object> M2ObjectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = M2)
		TSubclassOf<class AM2Base> M2BaseClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = M3)
		TSubclassOf<class AM3Object> M3Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = M3)
		TSubclassOf<class AM4Object> M4Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trap)
		TSubclassOf<class ATrapObject> TrapClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Food)
		TSubclassOf<class AFoodObject> FoodClass;

};
