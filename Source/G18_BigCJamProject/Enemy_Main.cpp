// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Main.h"

#include "PaperFlipbookComponent.h"
#include "PlayerChar.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy_Main::AEnemy_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyCollider"));
	SetRootComponent(EnemyCollider);

	EnemyAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EnemyAnimation"));
	EnemyAnimation->SetupAttachment(RootComponent);
	
	MovementSpeed = 50.0f;
	FiringDelayTime = 1.0f;
	TimeToNextShot = FiringDelayTime;
	MaximumHealth = 1.0f;
	CurrentHealth = MaximumHealth;
	ProjectileSpeed = 500.0f;
	ProjectileScale = FVector(1.0f, 1.0f, 1.0f);
	MovementDirection = 1;
	Player = nullptr;
	bPlayerPresent = false;
	FiringAngle = FRotator(0.0f, 0.0f, 0.0f);

	StartingDelayTime = 1.0f;
	TimeUntilBeginShooting = StartingDelayTime;
	FlashingDelayTime = 0.016667f;
	FlashingDelayTimeElapsed = FlashingDelayTime;
	bCanShoot = false;
}

// Called when the game starts or when spawned
void AEnemy_Main::BeginPlay()
{
	Super::BeginPlay();

	TimeUntilBeginShooting = StartingDelayTime;
	FlashingDelayTimeElapsed = FlashingDelayTime;

	TimeToNextShot = 0.0f;
	CurrentHealth = MaximumHealth;
	Player = Cast<APlayerChar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Player)
	{
		bPlayerPresent = true;
		FiringAngle = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
	}
	else
	{
		bPlayerPresent = false;
	}
}

// Called every frame
void AEnemy_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeUntilBeginShooting > 0.0f)
	{
		TimeUntilBeginShooting -= DeltaTime;

		if (FlashingDelayTimeElapsed > 0.0f)
		{
			FlashingDelayTimeElapsed -= DeltaTime;
		}
		else
		{
			if (EnemyCollider->bHiddenInGame == false)
			{
				EnemyCollider->SetHiddenInGame(true);
				EnemyAnimation->SetHiddenInGame(true);
			}
			else
			{
				EnemyCollider->SetHiddenInGame(false);
				EnemyAnimation->SetHiddenInGame(false);
			}
			FlashingDelayTimeElapsed = FlashingDelayTime;
		}
	}
	else
	{
		bCanShoot = true;
		EnemyCollider->SetHiddenInGame(false);
		EnemyAnimation->SetHiddenInGame(false);
	}

	FHitResult* MoveHit = new FHitResult;
	const bool Move = SetActorLocation(FVector(
		GetActorLocation().X,
		GetActorLocation().Y,
		(GetActorLocation().Z + ((MovementSpeed * MovementDirection) * DeltaTime))
		), true, MoveHit);

	if (!(Move))
	{
		if(MoveHit->Location.Z > GetActorLocation().Z)
		{
			MovementDirection = -1;
		}
		else if(MoveHit->Location.Z < GetActorLocation().Z)
		{
			MovementDirection = 1;
		}
	}

	delete MoveHit;

	Shooting(DeltaTime);
	
	if (CurrentHealth <= 0.0f)
	{
		Destroy();
	}
}

void AEnemy_Main::Shooting(float DeltaTime)
{
	if (bPlayerPresent)
	{
		FiringAngle = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
	}

	if (bCanShoot)
	{
		TimeToNextShot -= DeltaTime;

		if (TimeToNextShot <= 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("FIRE1"));

			if (ShotBP)
			{
				UE_LOG(LogTemp, Warning, TEXT("FIRE2"));

				const FRotator ShotRotation = FiringAngle;
				const FVector ShotLocation = GetActorLocation();

				const FActorSpawnParameters SpawnParams;

				AEnemyShot* ShotProjectile = (GetWorld()->SpawnActor<AEnemyShot>(ShotBP, ShotLocation, ShotRotation, SpawnParams));

				if (ShotProjectile)
				{
					UE_LOG(LogTemp, Warning, TEXT("FIRE3"));

					ShotProjectile->ShotMovement->InitialSpeed = ProjectileSpeed;
					ShotProjectile->ShotMovement->MaxSpeed = ProjectileSpeed;
					ShotProjectile->SetActorScale3D(ProjectileScale);
				}
				TimeToNextShot = FiringDelayTime;
			}
		}
	}
}

void AEnemy_Main::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerShot* MyPlayerShot = Cast<APlayerShot>(OtherActor);
	if (MyPlayerShot)
	{
		if (bCanShoot)
		{
			Destroy();
		}
	}
}

