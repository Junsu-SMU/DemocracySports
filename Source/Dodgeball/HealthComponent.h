// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DODGEBALL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The owner's initial and current amount health points
	UPROPERTY(EditDefaultsOnly, Category = Health)
		float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Vote)
		float Vote = 20.f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static float myVote;

	// Take health points from its owner
	void LoseHealth(float Amount); // ü�� ��� �Լ�
	void LoseVote(float Amount); // ��ǥ�� ��� �Լ�
	void GainVote(float Amount); // ��ǥ�� ��� �Լ�

	FORCEINLINE float GetHealthPercent() const { return Health; }
	FORCEINLINE float GetVotePercent() const { return Vote / 100.f; }
};
