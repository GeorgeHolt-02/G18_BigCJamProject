// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
//#include "PaperFlipbookComponent.h"

//FName APlayerChar::SpriteComponentName(TEXT("Sprite0"));

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region /* COMPONENT INITIALISATION */

	PlayerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCollider"));
	SetRootComponent(PlayerCollider);

	PlayerShotOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerShotOrigin"));
	PlayerShotOrigin->SetupAttachment(RootComponent);

	//// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 500.0f;
	//CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	//CameraBoom->SetUsingAbsoluteRotation(true);
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//// Create an orthographic camera (no perspective) and attach it to the boom
	//PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//PlayerCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//PlayerCamera->OrthoWidth = 2048.0f;
	//PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//// Prevent all automatic rotation behavior on the camera, character, and camera component
	//CameraBoom->SetUsingAbsoluteRotation(true);
	//PlayerCamera->bUsePawnControlRotation = false;
	//PlayerCamera->bAutoActivate = true;

	//PlayerAnimation = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(APlayerChar::SpriteComponentName);

#pragma endregion

#pragma region /* VARIABLE INITIALISATION */

	OriginalDistanceFromMouse = 0.0f;

	bClickHeld = false;

	MaxShots = 1;

	ShotTag = *FString(this->GetName() + "Shot");

	MousePrevPosition = FVector(0.0f, 0.0f, 0.0f);

#pragma endregion

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
	OnClicked.AddDynamic(this, &APlayerChar::OnClick);
	
	MousePrevPosition = GetMouseTransform().MouseLocation;
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerPosition();

	if (bClickHeld)
	{
		if ((GetMouseTransform().MouseLocation.X - MousePrevPosition.X) < 0.0f)
		{
			Shoot();
		}
	}

	MousePrevPosition = GetMouseTransform().MouseLocation;
}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Release", IE_Released, this, &APlayerChar::OnRelease);
}


void APlayerChar::OnClick(AActor* TouchedActor, FKey ButtonPressed)
{
	FHitResult OutHit;
	bool LineTrace = GetWorld()->LineTraceSingleByChannel(OutHit, GetMouseTransform().MouseLocation,
		(GetMouseTransform().MouseLocation + (GetMouseTransform().MouseDirection * 10000.0f)), ECC_GameTraceChannel1,
		FCollisionQueryParams::DefaultQueryParam, FCollisionResponseParams::DefaultResponseParam);

	if (LineTrace)
	{
		if (OutHit.GetComponent()->Mobility == EComponentMobility::Movable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Clicked"));

			bClickHeld = true;

			OriginalDistanceFromMouse = OutHit.Distance;

			SetActorLocation(FVector(
				GetActorLocation().X,
				GetActorLocation().Y,
				GetMouseTransform().MouseLocation.Z + (GetMouseTransform().MouseDirection.Z * OriginalDistanceFromMouse)
			), true);
		}
	}
}

void APlayerChar::OnRelease()
{
	if (bClickHeld)
	{
		UE_LOG(LogTemp, Warning, TEXT("Released"));

		bClickHeld = false;
	}
}

void APlayerChar::Shoot()
{
	if (Controller != nullptr)
	{
		const FRotator ShotRotation = PlayerShotOrigin->GetComponentRotation();
		const FVector ShotLocation = PlayerShotOrigin->GetComponentLocation();

		if (bCanShoot())
		{
			if (ShotBP)
			{
				const FActorSpawnParameters SpawnParams;

				APlayerShot* ShotProjectile = (GetWorld()->SpawnActor<APlayerShot>(ShotBP, ShotLocation, ShotRotation, SpawnParams));
				if (ShotProjectile)
				{
					ShotProjectile->Tags.Add(ShotTag);
				}
			}
		}
	}
}

bool APlayerChar::bCanShoot()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ShotBP, FoundShots);

	int ShotNum = 0;

	for (const auto& Shot : FoundShots)
	{
		if (Shot->ActorHasTag(ShotTag))
		{
			ShotNum++;
		}
	}

	if (ShotNum >= MaxShots)
	{
		return false;
	}

	return true;
}

void APlayerChar::UpdatePlayerPosition()
{
	FVector Location = GetMouseTransform().MouseLocation;
	FVector Direction = GetMouseTransform().MouseDirection;

	if (bClickHeld)
	{
		SetActorLocation(FVector(
			GetActorLocation().X,
			GetActorLocation().Y,
			Location.Z + (Direction.Z * OriginalDistanceFromMouse)
		), true);
	}
}

FMouseTransform APlayerChar::GetMouseTransform()
{
	FMouseTransform MouseTransform;

	FVector MouseLocation, MouseDirection;

	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	MouseTransform.MouseLocation = MouseLocation;
	MouseTransform.MouseDirection = MouseDirection;

	return MouseTransform;
}
