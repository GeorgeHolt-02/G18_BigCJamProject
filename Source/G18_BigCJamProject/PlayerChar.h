// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerShot.h"
#include "GameFramework/Pawn.h"
#include "PlayerChar.generated.h"

USTRUCT(BlueprintType)
struct FMouseTransform
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector MouseLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector MouseDirection;

	FMouseTransform()
	{
		MouseLocation = FVector(0.0f, 0.0f, 0.0f);
		MouseDirection = FVector(0.0f, 0.0f, 0.0f);
	}
};

UCLASS()
class G18_BIGCJAMPROJECT_API APlayerChar : public APawn
{
	GENERATED_BODY()

#pragma region /* PLAYER CAMERA */
	
	////Player camera
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* PlayerCamera;

	///** Camera boom positioning the camera */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

#pragma endregion

	//// Name of the Sprite component
	//static FName SpriteComponentName;

public:
	// Sets default values for this pawn's properties
	APlayerChar();

#pragma region /* STANDARD VARIABLES */

	//Distance between player and the mouse on the previous frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float OriginalDistanceFromMouse;

	//Whether or not the player is being held with the mouse
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bClickHeld;

	//The maximum number of projectiles that can be in the scene at once
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
		int MaxShots;

	//The number of fired projectiles currently in the scene
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		TArray<AActor*> FoundShots;

	//The name of the projectile currently being checked when determining whether or not the player can fire again
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		FName ShotTag;

	//Difference in mouse position since last frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector MousePrevPosition;

	//Player collider/hitbox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* PlayerCollider;

	//Default player sprite animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprite")
	class UPaperFlipbookComponent* PlayerAnimation;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region /* MAIN COMPONENTS */

	//Player firing origin transform
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	USceneComponent* PlayerShotOrigin;

	//Projectile blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
		TSubclassOf<APlayerShot> ShotBP;

#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region /* STANDARD FUNCTIONS */

	UFUNCTION()
	void UpdatePlayerPosition();

	//Shooting function
	UFUNCTION()
	void Shoot();

#pragma endregion

#pragma region /* DELEGATE-BOUND FUNCTIONS */

	UFUNCTION()
	void OnClick(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	void OnRelease();

	// Called on an overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region /* "GET" FUNCTIONS */

	//Returns the player
	UFUNCTION(BlueprintCallable)
	FMouseTransform GetMouseTransform();

	//Returns whether or not the player can shoot
	UFUNCTION()
	bool bCanShoot();

#pragma endregion

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
