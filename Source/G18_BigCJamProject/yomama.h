// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "yomama.generated.h"

UCLASS()
class G18_BIGCJAMPROJECT_API Ayomama : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Ayomama();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
