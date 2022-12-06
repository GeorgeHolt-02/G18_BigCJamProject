// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerChar.generated.h"

UCLASS()
class G18_BIGCJAMPROJECT_API APlayerChar : public APawn
{
	GENERATED_BODY()

	#pragma region Player Camera 
	//Player camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	/** Camera boom positioning the camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	#pragma endregion

	//// Name of the Sprite component
	//static FName SpriteComponentName;

public:
	// Sets default values for this pawn's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	#pragma region Main Properties
	//Player transform
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USceneComponent* PlayerTransform;

	//Player collider/hitbox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* PlayerCollider;

	////Default player sprite animation
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UPaperFlipbook* PlayerAnimation;
	#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
