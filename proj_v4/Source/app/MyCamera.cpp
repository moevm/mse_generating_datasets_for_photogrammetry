// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamera.h"

// Sets default values
AMyCamera::AMyCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = mesh;
	meshVector = startPositionMesh;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 500.f;
	springArm->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mesh->SetWorldLocation(meshVector);

	FRotator newYaw = GetActorRotation();
	newYaw.Yaw = angleInput.X;
	SetActorRotation(newYaw);

	FRotator newRoll = springArm->GetComponentRotation();
	newRoll.Roll = FMath::Clamp(angleInput.Z, -180.f, 180.f);
	springArm->SetWorldRotation(newRoll); 

	FRotator newPitch = springArm->GetComponentRotation();
	newPitch.Pitch = FMath::Clamp(angleInput.Y, -90.f, 0.f);
	springArm->SetWorldRotation(newPitch);

	

	springArm->TargetArmLength = FMath::FInterpTo(springArm->TargetArmLength, DesiredArmLength, DeltaTime, 5.0f);
}

// Called to bind functionality to input
void AMyCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCamera::SetCameraYaw(float axis)
{
	angleInput.X = axis;
}

void AMyCamera::SetCameraPitch(float axis)
{
		angleInput.Y = axis * (-1);	
}
void AMyCamera::SetCameraRoll(float axis)
{
	angleInput.Z = axis;
}

void AMyCamera::SetArmLenght(float axis)
{
	DesiredArmLength = axis;
}

void AMyCamera::SetMeshVectorX(float axis)
{
	meshVector.X = axis;
}

void AMyCamera::SetMeshVectorY(float axis)
{
	meshVector.Y = axis;
}


void AMyCamera::SetMeshVectorZ(float axis)
{
	if (axis >= 50.f)
		meshVector.Z = axis;
	else
		axis = 50.f;
}

