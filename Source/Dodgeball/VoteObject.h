// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoteObject.generated.h"

class USphereComponent;

UCLASS()
class DODGEBALL_API AVoteObject : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = VoteUp)
		float VoteUp = 1.f; // 투표율증가 1

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* VoteGainSound;

public:

	AVoteObject();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt 함수
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);



};
