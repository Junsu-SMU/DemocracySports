// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M2Object.generated.h"

UCLASS()
class DODGEBALL_API AM2Object : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* M2touchSound;

public:
	AM2Object();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static bool M2Put;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt ÇÔ¼ö
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
