// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShot.generated.h"

UCLASS()
class G18_BIGCJAMPROJECT_API AEnemyShot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyShot();

	/* Shot collision */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* ShotCollider;

	/* Shot movement component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ShotMovement;

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

	// Called on an overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
