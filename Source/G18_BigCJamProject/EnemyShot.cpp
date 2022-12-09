// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShot.h"

#include "PaperFlipbookComponent.h"
#include "PlayerChar.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemyShot::AEnemyShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShotCollider = CreateDefaultSubobject<USphereComponent>(TEXT("ShotCollider"));
	SetRootComponent(ShotCollider);

	ShotMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ShotMovement"));

	ShotMovement->InitialSpeed = 500.0f;
	ShotMovement->MaxSpeed = ShotMovement->InitialSpeed;
	ShotMovement->Velocity = FVector(1.0f, 0.0f, 0.0f);
	ShotMovement->bRotationFollowsVelocity = true;
	ShotMovement->ProjectileGravityScale = 0.0f;
	ShotMovement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 0.0f));
	ShotMovement->bConstrainToPlane = false;

	ShotCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MaxTimeBeforeKill = 10.0f;

	TimeBeforeKill = MaxTimeBeforeKill;
}

// Called when the game starts or when spawned
void AEnemyShot::BeginPlay()
{
	Super::BeginPlay();
	
	ShotCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyShot::OnOverlapBegin);

	TimeBeforeKill = MaxTimeBeforeKill;
}

// Called every frame
void AEnemyShot::Tick(float DeltaTime)
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

void AEnemyShot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerChar* MyPlayerChar = Cast<APlayerChar>(OtherActor);
	if (MyPlayerChar)
	{
		MyPlayerChar->PlayerAnimation->SetVisibility(false);
		MyPlayerChar->PlayerCollider->SetHiddenInGame(true);
		MyPlayerChar->PlayerCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyPlayerChar->SetActorTickEnabled(false);
		Destroy();
	}
}

