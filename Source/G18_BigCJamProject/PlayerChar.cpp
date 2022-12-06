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

	PlayerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCollider"));
	SetRootComponent(PlayerCollider);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Create an orthographic camera (no perspective) and attach it to the boom
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	PlayerCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	PlayerCamera->OrthoWidth = 2048.0f;
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	PlayerCamera->bUsePawnControlRotation = false;
	PlayerCamera->bAutoActivate = true;

	//PlayerAnimation = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(APlayerChar::SpriteComponentName);
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
	OnClicked.AddDynamic(this, &APlayerChar::OnClick);

}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!(UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor))
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	}
	
	if (!(UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents))
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
	}
}

void APlayerChar::OnClick(AActor* TouchedActor, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

