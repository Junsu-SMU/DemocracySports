// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "HealthInterface.h"
#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"

float UHealthComponent::myVote = 20;

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UHealthComponent::myVote = 20;
	Health = ADodgeballCharacter::playerhp;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UHealthComponent::LoseHealth(float Amount) // ü�� ��� �Լ�
{
	Health -= Amount; // ü���� Amount����ŭ �����.
	if (Health > ADodgeballCharacter::playerhp)
	{
		Health = ADodgeballCharacter::playerhp;
	}
	if (GetOwner()->Implements<UHealthInterface>()) // ü���� 0���� ������ OnTakeDamage
	{
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}
	if (Health <= 0.f) // ü���� 0���� ������ OnDeath
	{
		Health = 0.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

void UHealthComponent::LoseVote(float Amount) // ��ǥ�� ��� �Լ�
{
	Vote -= Amount; // ��ǥ���� Amount����ŭ �����.
	UHealthComponent::myVote -= Amount;
	if (GetOwner()->Implements<UHealthInterface>()) // ��ǥ���� 0���� ������ OnTakeDamage
	{
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}
	if (Vote <= 0.f) // ��ǥ���� 0���� ������ OnDeath
	{
		Vote = 0.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

void UHealthComponent::GainVote(float Amount) // ��ǥ�� �ø��� �Լ�
{
	Vote += Amount; // ��ǥ���� Amount����ŭ ���δ�.
	UHealthComponent::myVote += Amount;
	if (GetOwner()->Implements<UHealthInterface>()) // ��ǥ���� 0���� ������ OnTakeDamage
	{
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}

	if (Vote > 25.f && ADodgeballPlayerController::CurrentLevel == 0) // 1���� �� Ŭ���� ���� �޼� ��
	{
		Vote = 20.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			if (ADodgeballPlayerController::ReachedLevel == 0)
			{
				ADodgeballPlayerController::ReachedLevel = 1;
			}
			ADodgeballPlayerController::Gold += 1000;
			IHealthInterface::Execute_OnClear(GetOwner());
		}
	}
	else if (Vote > 30.f && ADodgeballPlayerController::CurrentLevel == 1) // 2���� �� Ŭ���� ���� �޼� ��
	{
		Vote = 20.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			if (ADodgeballPlayerController::ReachedLevel == 1)
			{
				ADodgeballPlayerController::ReachedLevel = 2;
			}
			ADodgeballPlayerController::Gold += 2000;
			IHealthInterface::Execute_OnClear(GetOwner());
		}
	}
	else if (Vote > 35.f && ADodgeballPlayerController::CurrentLevel == 2) // 3���� �� Ŭ���� ���� �޼� ��
	{
		Vote = 20.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			if (ADodgeballPlayerController::ReachedLevel == 2)
			{
				ADodgeballPlayerController::ReachedLevel = 3;
			}
			ADodgeballPlayerController::Gold += 3000;
			IHealthInterface::Execute_OnClear(GetOwner());
		}
	}
	else if (Vote > 40.f && ADodgeballPlayerController::CurrentLevel == 3) // 4���� �� Ŭ���� ���� �޼� ��
	{
		Vote = 20.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			if (ADodgeballPlayerController::ReachedLevel == 3)
			{
				ADodgeballPlayerController::ReachedLevel = 4;
			}
			ADodgeballPlayerController::Gold += 4000;
			IHealthInterface::Execute_OnClear(GetOwner());
		}
	}
	else if (Vote > 45.f && ADodgeballPlayerController::CurrentLevel == 4) // 5���� �� Ŭ���� ���� �޼� ��
	{
		Vote = 20.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			ADodgeballPlayerController::Gold += 5000;
			IHealthInterface::Execute_OnClear(GetOwner());
		}
	}
}