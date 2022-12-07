// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShot.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APlayerShot::APlayerShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShotCollider = CreateDefaultSubobject<USphereComponent>(TEXT("ShotCollider"));
	SetRootComponent(ShotCollider);

	ShotMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ShotMovement"));

	ShotMovement->InitialSpeed = 500.0f;
	ShotMovement->MaxSpeed = 0.0f;
	ShotMovement->Velocity = FVector(1.0f, 0.0f, 0.0f);
	ShotMovement->bRotationFollowsVelocity = true;
	ShotMovement->ProjectileGravityScale = 0.0f;
	ShotMovement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 0.0f));
	ShotMovement->bConstrainToPlane = false;

	ShotCollider ->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Damage = 1.0f;

	MaxTimeBeforeKill = 5.0f;

	TimeBeforeKill = MaxTimeBeforeKill;
}

// Called when the game starts or when spawned
void APlayerShot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShotCollider->GetCollisionEnabled() != ECollisionEnabled::QueryAndPhysics)
	{
		ShotCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	TimeBeforeKill -= DeltaTime;

	if (TimeBeforeKill <= 0.0f)
	{
		Destroy();
	}
}

void APlayerShot::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	Destroy();
}

