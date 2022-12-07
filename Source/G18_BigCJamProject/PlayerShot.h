// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerShot.generated.h"

UCLASS()
class G18_BIGCJAMPROJECT_API APlayerShot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerShot();

	/* Shot collision */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* ShotCollider;

	/* Shot movement component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ShotMovement;

	/* The base damage the shot deals */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;

	/* Maximum time before shot is destroyed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxTimeBeforeKill;

	/* Current time before shot is destroyed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeBeforeKill;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called on a hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& HitResult);
};
