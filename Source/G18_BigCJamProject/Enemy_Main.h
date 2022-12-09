// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyShot.h"
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

	//Time until next shot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeToNextShot;

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

	//Movement direction (1 for up, -1 for down)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int MovementDirection;

	//Player character
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class APlayerChar* Player;

	//Firing angle
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator FiringAngle;

	//Is there a player character?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bPlayerPresent;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AEnemyShot> ShotBP;

#pragma endregion 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region /* STANDARD FUNCTIONS */

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Shooting(float DeltaTime);

#pragma endregion 

#pragma region /* DELEGATE-BOUND FUNCTIONS */
	
	// Called on an overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion	
	
};
