// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = mesh;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 500.f;
	springArm->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator newYaw = GetActorRotation();
	FRotator newPitch = springArm->GetComponentRotation();
	newYaw.Yaw += mouseInput.X;
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.f, 0.f);
	SetActorRotation(newYaw);
	springArm->SetWorldRotation(newPitch);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MouseYaw", this, &AMyPawn::MouseYaw);
	InputComponent->BindAxis("MousePitch", this, &AMyPawn::MousePitch);

}

void AMyPawn::MouseYaw(float axis) {
	mouseInput.X = axis;

}

void AMyPawn::MousePitch(float axis) {
	mouseInput.Y = axis;

}

void AMyPawn::CheckInputData(FString input)
{

}

void AMyPawn::ReadPosCoord(FString input)
{

}