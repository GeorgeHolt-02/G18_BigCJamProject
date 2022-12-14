// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShot.h"

#include "Enemy_Main.h"
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

	ShotCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Damage = 1.0f;

	MaxTimeBeforeKill = 5.0f;

	TimeBeforeKill = 0.0f;
}

// Called when the game starts or when spawned
void APlayerShot::BeginPlay()
{
	Super::BeginPlay();

	ShotCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerShot::OnOverlapBegin);
	
	TimeBeforeKill = MaxTimeBeforeKill;
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

void APlayerShot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy_Main* MyEnemy = Cast<AEnemy_Main>(OtherActor);
	if(MyEnemy)
	{
		MyEnemy->CurrentHealth -= Damage;
	}
	Destroy();
}

