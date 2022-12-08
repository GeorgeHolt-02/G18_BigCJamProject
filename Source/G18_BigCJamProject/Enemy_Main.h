// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Main.generated.h"

UCLASS()
class G18_BIGCJAMPROJECT_API AEnemy_Main : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Main();

#pragma region /* STANDARD VARIABLES */

	//Movement speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MovementSpeed;

	//Firing frequency
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FiringFrequency;

	//Maximum health
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaximumHealth;

	//Current health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	//Shot travel speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ProjectileSpeed;

	//Shot size
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector ProjectileScale;

#pragma endregion 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region /* MAIN COMPONENTS */

	//Enemy collider/hitbox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* EnemyCollider;

	//Default enemy sprite animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbookComponent* EnemyAnimation;
	
	//Projectile blueprint
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	//TSubclassOf<APlayerShot> ShotBP;

#pragma endregion 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
