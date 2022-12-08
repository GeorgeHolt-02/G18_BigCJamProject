// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Main.h"

// Sets default values
AEnemy_Main::AEnemy_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Main::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

