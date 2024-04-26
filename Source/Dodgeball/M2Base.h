// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M2Base.generated.h"

UCLASS()
class DODGEBALL_API AM2Base : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* M2BaseSound;

public:
	AM2Base();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static int M2Count;
	static bool M2delete;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt ÇÔ¼ö
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
